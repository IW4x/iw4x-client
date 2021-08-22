#include "STDInclude.hpp"

namespace Components
{
	Utils::Signal<Renderer::BackendCallback> Renderer::BackendFrameSignal;
	Utils::Signal<Renderer::BackendCallback> Renderer::SingleBackendFrameSignal;

	Utils::Signal<Scheduler::Callback> Renderer::EndRecoverDeviceSignal;
	Utils::Signal<Scheduler::Callback> Renderer::BeginRecoverDeviceSignal;

	Dvar::Var Renderer::DrawTriggers;
	Dvar::Var Renderer::DrawSceneModelCollisions;
	Dvar::Var Renderer::DrawSceneModelBoundingBoxes;
	Dvar::Var Renderer::DrawModelNames;
	Dvar::Var Renderer::DrawAABBTrees;

	__declspec(naked) void Renderer::FrameStub()
	{
		__asm
		{
			pushad
			call Scheduler::FrameHandler
			popad

			push 5AC950h
			retn
		}
	}

	__declspec(naked) void Renderer::BackendFrameStub()
	{
		__asm
		{
			pushad
			call Renderer::BackendFrameHandler
			popad

			mov eax, ds:66E1BF0h
			push 536A85h
			retn
		}
	}

	void Renderer::BackendFrameHandler()
	{
		IDirect3DDevice9* device = *Game::dx_ptr;

		if (device)
		{
			device->AddRef();

			Renderer::BackendFrameSignal(device);

			Utils::Signal<Renderer::BackendCallback> copy(Renderer::SingleBackendFrameSignal);
			Renderer::SingleBackendFrameSignal.clear();
			copy(device);

			device->Release();
		}
	}

	void Renderer::OnNextBackendFrame(Utils::Slot<Renderer::BackendCallback> callback)
	{
		Renderer::SingleBackendFrameSignal.connect(callback);
	}

	void Renderer::OnBackendFrame(Utils::Slot<Renderer::BackendCallback> callback)
	{
		Renderer::BackendFrameSignal.connect(callback);
	}

	void Renderer::OnDeviceRecoveryEnd(Utils::Slot<Scheduler::Callback> callback)
	{
		Renderer::EndRecoverDeviceSignal.connect(callback);
	}

	void Renderer::OnDeviceRecoveryBegin(Utils::Slot<Scheduler::Callback> callback)
	{
		Renderer::BeginRecoverDeviceSignal.connect(callback);
	}

	int Renderer::Width()
	{
		return reinterpret_cast<LPPOINT>(0x66E1C68)->x;
	}

	int Renderer::Height()
	{
		return reinterpret_cast<LPPOINT>(0x66E1C68)->y;
	}

	void Renderer::PreVidRestart()
	{
		Renderer::BeginRecoverDeviceSignal();
	}

	void Renderer::PostVidRestart()
	{
		Renderer::EndRecoverDeviceSignal();
	}

	__declspec(naked) void Renderer::PostVidRestartStub()
	{
		__asm
		{
			pushad
			call Renderer::PostVidRestart
			popad

			push 4F84C0h
			retn
		}
	}

	void Renderer::R_TextureFromCodeError(const char* sampler, Game::GfxCmdBufState* state)
	{
		Game::Com_Error(0, "Tried to use sampler '%s' when it isn't valid for material '%s' and technique '%s'",
			sampler, state->material->info.name, state->technique->name);
	}

	__declspec(naked) void Renderer::StoreGfxBufContextPtrStub1()
	{
		__asm
		{
			// original code
			mov eax, DWORD PTR[eax * 4 + 0066E600Ch];

			// store GfxCmdBufContext
			/*push edx;
			mov edx, [esp + 24h];
			mov gfxState, edx;
			pop edx;*/

			// show error
			pushad;
			push [esp + 24h + 20h];
			push eax;
			call R_TextureFromCodeError;
			add esp, 8;
			popad;

			// go back
			push 0x0054CAC1;
			retn;
		}
	}

	__declspec(naked) void Renderer::StoreGfxBufContextPtrStub2()
	{
		__asm
		{
			// original code
			mov edx, DWORD PTR[eax * 4 + 0066E600Ch];

			// show error
			pushad;
			push ebx;
			push edx;
			call R_TextureFromCodeError;
			add esp, 8;
			popad;

			// go back
			push 0x0054CFA4;
			retn;
		}
	}

	int Renderer::DrawTechsetForMaterial(int a1, float a2, float a3, const char* material, Game::vec4_t* color, int a6)
	{
		auto mat = Game::DB_FindXAssetHeader(Game::XAssetType::ASSET_TYPE_MATERIAL, Utils::String::VA("wc/%s", material)).material;
		return Utils::Hook::Call<int(int, float, float, const char*, Game::vec4_t*, int)>(0x005033E0)(a1, a2, a3, Utils::String::VA("%s (^3%s^7)", mat->info.name, mat->techniqueSet->name), color, a6);
	}

	void Renderer::DebugDrawTriggers()
	{
		if (!DrawTriggers.get<bool>()) return;

		float hurt[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float hurtTouch[4] = { 0.75f, 0.0f, 0.0f, 1.0f };
		float damage[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		float once[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
		float multiple[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

		auto* entities = Game::g_entities;

		for (auto i = 0u; i < 0x800; i++)
		{
			auto* ent = &entities[i];

			if (ent->r.isInUse)
			{
				Game::Bounds b = ent->r.box;
				b.midPoint[0] += ent->r.currentOrigin[0];
				b.midPoint[1] += ent->r.currentOrigin[1];
				b.midPoint[2] += ent->r.currentOrigin[2];

				switch (ent->handler)
				{
				case Game::ENT_HANDLER_TRIGGER_HURT:
					Game::R_AddDebugBounds(hurt, &b);
					break;

				case Game::ENT_HANDLER_TRIGGER_HURT_TOUCH:
					Game::R_AddDebugBounds(hurtTouch, &b);
					break;

				case Game::ENT_HANDLER_TRIGGER_DAMAGE:
					Game::R_AddDebugBounds(damage, &b);
					break;

				case Game::ENT_HANDLER_TRIGGER_MULTIPLE:
					if (ent->spawnflags & 0x40)
						Game::R_AddDebugBounds(once, &b);
					else
						Game::R_AddDebugBounds(multiple, &b);
					break;

				default:
					float rv = std::min((float)ent->handler, (float)5) / 5;
					float gv = std::clamp((float)ent->handler - 5, (float)0, (float)5) / 5;
					float bv = std::clamp((float)ent->handler - 10, (float)0, (float)5) / 5;

					float color[4] = { rv, gv, bv, 1.0f };

					Game::R_AddDebugBounds(color, &b);
					break;
				}
			}
		}
	}

	void Renderer::DebugDrawSceneModelCollisions()
	{
		if (!DrawSceneModelCollisions.get<bool>()) return;

		float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

		auto* scene = Game::scene;

		for (auto i = 0; i < scene->sceneModelCount; i++)
		{
			if (!scene->sceneModel[i].model)
				continue;

			for (auto j = 0; j < scene->sceneModel[i].model->numCollSurfs; j++)
			{
				auto b = scene->sceneModel[i].model->collSurfs[j].bounds;
				b.midPoint[0] += scene->sceneModel[i].placement.base.origin[0];
				b.midPoint[1] += scene->sceneModel[i].placement.base.origin[1];
				b.midPoint[2] += scene->sceneModel[i].placement.base.origin[2];
				b.halfSize[0] *= scene->sceneModel[i].placement.scale;
				b.halfSize[1] *= scene->sceneModel[i].placement.scale;
				b.halfSize[2] *= scene->sceneModel[i].placement.scale;

				Game::R_AddDebugBounds(green, &b, &scene->sceneModel[i].placement.base.quat);
			}
		}
	}

	void Renderer::DebugDrawSceneModelBoundingBoxes()
	{
		if (!DrawSceneModelBoundingBoxes.get<bool>()) return;

		float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

		auto* scene = Game::scene;

		for (auto i = 0; i < scene->sceneModelCount; i++)
		{
			if (!scene->sceneModel[i].model)
				continue;

			auto b = scene->sceneModel[i].model->bounds;
			b.midPoint[0] += scene->sceneModel[i].placement.base.origin[0];
			b.midPoint[1] += scene->sceneModel[i].placement.base.origin[1];
			b.midPoint[2] += scene->sceneModel[i].placement.base.origin[2];
			b.halfSize[0] *= scene->sceneModel[i].placement.scale;
			b.halfSize[1] *= scene->sceneModel[i].placement.scale;
			b.halfSize[2] *= scene->sceneModel[i].placement.scale;
			Game::R_AddDebugBounds(red, &b, &scene->sceneModel[i].placement.base.quat);
		}

		for (auto i = 0; i < scene->sceneDObjCount; i++)
		{
			scene->sceneDObj[i].cull.bounds.halfSize[0] = std::abs(scene->sceneDObj[i].cull.bounds.halfSize[0]);
			scene->sceneDObj[i].cull.bounds.halfSize[1] = std::abs(scene->sceneDObj[i].cull.bounds.halfSize[1]);
			scene->sceneDObj[i].cull.bounds.halfSize[2] = std::abs(scene->sceneDObj[i].cull.bounds.halfSize[2]);

			if (scene->sceneDObj[i].cull.bounds.halfSize[0] < 0 ||
				scene->sceneDObj[i].cull.bounds.halfSize[1] < 0 ||
				scene->sceneDObj[i].cull.bounds.halfSize[2] < 0)
			{

				Components::Logger::Print("WARNING: Negative half size for DOBJ %s, this will cause culling issues!", scene->sceneDObj[i].obj->models[0]->name);
			}

			Game::R_AddDebugBounds(blue, &scene->sceneDObj[i].cull.bounds);
		}
	}

	void Renderer::DebugDrawModelNames()
	{
		auto val = DrawModelNames.get<Game::dvar_t*>()->current.integer;

		if (!val) return;

		float sceneModelsColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
		float dobjsColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
		float staticModelsColor[4] = { 1.0f, 0.0f, 1.0f, 1.0f };

		auto mapName = Dvar::Var("mapname").get<const char*>();
		auto* scene = Game::scene;
		auto world = Game::DB_FindXAssetEntry(Game::XAssetType::ASSET_TYPE_GFXWORLD, Utils::String::VA("maps/mp/%s.d3dbsp", mapName))->asset.header.gfxWorld;

		if (val == 1)
		{
			for (auto i = 0; i < scene->sceneModelCount; i++)
			{
				if (!scene->sceneModel[i].model)
					continue;

				Game::R_AddDebugString(sceneModelsColor, scene->sceneModel[i].placement.base.origin, 1.0, scene->sceneModel[i].model->name);
			}
		}

		else if (val == 2)
		{
			for (auto i = 0; i < scene->sceneDObjCount; i++)
			{
				if (scene->sceneDObj[i].obj)
				{
					for (int j = 0; j < scene->sceneDObj[i].obj->numModels; j++)
					{
						Game::R_AddDebugString(dobjsColor, scene->sceneDObj[i].placement.origin, 1.0, scene->sceneDObj[i].obj->models[j]->name);
					}
				}
			}
		}

		else if (val == 3)
		{
			// Static models
			for (size_t i = 0; i < world->dpvs.smodelCount; i++)
			{
				auto staticModel = world->dpvs.smodelDrawInsts[i];
				if (staticModel.model)
				{
					Game::R_AddDebugString(staticModelsColor, staticModel.placement.origin, 1.0, staticModel.model->name);
				}
			}
		}
	}

	void Renderer::DebugDrawAABBTrees()
	{
		if (!DrawAABBTrees.get<bool>()) return;

		float cyan[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
		float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

		Game::clipMap_t* clipMap = *reinterpret_cast<Game::clipMap_t**>(0x7998E0);
		//Game::GfxWorld* gameWorld = *reinterpret_cast<Game::GfxWorld**>(0x66DEE94);
		if (!clipMap) return;

		for (unsigned short i = 0; i < clipMap->smodelNodeCount; ++i)
		{
			Game::R_AddDebugBounds(cyan, &clipMap->smodelNodes[i].bounds);
		}

		for (unsigned int i = 0; i < clipMap->numStaticModels; i += 2)
		{
			Game::R_AddDebugBounds(red, &clipMap->staticModelList[i].absBounds);
		}
	}

	Renderer::Renderer()
	{
		if (Dedicated::IsEnabled()) return;

		Scheduler::OnFrame([]()
		{
			if (Game::CL_IsCgameInitialized()) 
			{
				DebugDrawAABBTrees();
				DebugDrawModelNames();
				DebugDrawSceneModelBoundingBoxes();
				DebugDrawSceneModelCollisions();
				DebugDrawTriggers();
			}
		});

		// 		Renderer::OnBackendFrame([] (IDirect3DDevice9* device)
		// 		{
		// 			if (Game::Sys_Milliseconds() % 2)
		// 			{
		// 				device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, 0, 0);
		// 			}
		//
		// 			return;
		//
		// 			IDirect3DSurface9* buffer = nullptr;
		//
		// 			device->CreateOffscreenPlainSurface(Renderer::Width(), Renderer::Height(), D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &buffer, nullptr);
		// 			device->GetFrontBufferData(0, buffer);
		//
		// 			if (buffer)
		// 			{
		// 				D3DSURFACE_DESC desc;
		// 				D3DLOCKED_RECT lockedRect;
		//
		// 				buffer->GetDesc(&desc);
		//
		// 				HRESULT res = buffer->LockRect(&lockedRect, NULL, D3DLOCK_READONLY);
		//
		//
		// 				buffer->UnlockRect();
		// 			}
		// 		});

				// Log broken materials
		Utils::Hook(0x0054CAAA, Renderer::StoreGfxBufContextPtrStub1, HOOK_JUMP).install()->quick();
		Utils::Hook(0x0054CF8D, Renderer::StoreGfxBufContextPtrStub2, HOOK_JUMP).install()->quick();

		// Enhance cg_drawMaterial
		Utils::Hook::Set(0x005086DA, "^3solid^7");
		Utils::Hook(0x00580F53, Renderer::DrawTechsetForMaterial, HOOK_CALL).install()->quick();

		// Frame hook
		Utils::Hook(0x5ACB99, Renderer::FrameStub, HOOK_CALL).install()->quick();

		Utils::Hook(0x536A80, Renderer::BackendFrameStub, HOOK_JUMP).install()->quick();

		// Begin device recovery (not D3D9Ex)
		Utils::Hook(0x508298, []()
		{
			Game::DB_BeginRecoverLostDevice();
			Renderer::BeginRecoverDeviceSignal();
		}, HOOK_CALL).install()->quick();

			// End device recovery (not D3D9Ex)
		Utils::Hook(0x508355, []()
		{
			Renderer::EndRecoverDeviceSignal();
			Game::DB_EndRecoverLostDevice();
		}, HOOK_CALL).install()->quick();

		// Begin vid_restart
		Utils::Hook(0x4CA2FD, Renderer::PreVidRestart, HOOK_CALL).install()->quick();

		// End vid_restart
		Utils::Hook(0x4CA3A7, Renderer::PostVidRestartStub, HOOK_CALL).install()->quick();


		Dvar::OnInit([]
		{
			static std::vector < char * > values =
			{
				const_cast<char*>("Disabled"),
				const_cast<char*>("Scene Models"),
				const_cast<char*>("Scene Dynamic Objects"),
				const_cast<char*>("GfxWorld Static Models"),
				nullptr
			};

			Renderer::DrawSceneModelBoundingBoxes = Game::Dvar_RegisterBool("r_drawSceneModelBoundingBoxes", false, Game::DVAR_FLAG_CHEAT, "Draw scene model bounding boxes");
			Renderer::DrawSceneModelCollisions = Game::Dvar_RegisterBool("r_drawSceneModelCollisions", false, Game::DVAR_FLAG_CHEAT, "Draw scene model collisions");
			Renderer::DrawTriggers = Game::Dvar_RegisterBool("r_drawTriggers", false, Game::DVAR_FLAG_CHEAT, "Draw triggers");
			Renderer::DrawModelNames = Game::Dvar_RegisterEnum("r_drawModelNames", values.data(), 0, Game::DVAR_FLAG_CHEAT, "Draw all model names");
			Renderer::DrawAABBTrees = Game::Dvar_RegisterBool("r_drawAabbTrees", false, Game::DVAR_FLAG_CHEAT, "Draw aabb trees");
		});

	}

	Renderer::~Renderer()
	{
		Renderer::BackendFrameSignal.clear();
		Renderer::SingleBackendFrameSignal.clear();

		Renderer::EndRecoverDeviceSignal.clear();
		Renderer::BeginRecoverDeviceSignal.clear();
	}
}
