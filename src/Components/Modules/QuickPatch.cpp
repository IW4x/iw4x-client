#include <STDInclude.hpp>
#include <Utils/Compression.hpp>

#include "QuickPatch.hpp"
#include "TextRenderer.hpp"
#include "Toast.hpp"

namespace Components
{
	Dvar::Var QuickPatch::UIMousePitch;

	Dvar::Var QuickPatch::r_customAspectRatio;

	void QuickPatch::UnlockStats()
	{
		if (Dedicated::IsEnabled()) return;

		if (Game::CL_IsCgameInitialized())
		{
			Toast::Show("cardicon_locked", "^1Error", "Not allowed while ingame.", 3000);
			return;
		}

		Command::Execute("setPlayerData prestige 10");
		Command::Execute("setPlayerData experience 2516000");
		Command::Execute("setPlayerData iconUnlocked cardicon_prestige10_02 1");

		// Unlock challenges
		Game::StringTable* challengeTable = Game::DB_FindXAssetHeader(Game::XAssetType::ASSET_TYPE_STRINGTABLE, "mp/allchallengestable.csv").stringTable;

		if (challengeTable)
		{
			for (int i = 0; i < challengeTable->rowCount; ++i)
			{
				// Find challenge
				const char* challenge = Game::TableLookup(challengeTable, i, 0);

				int maxState = 0;
				int maxProgress = 0;

				// Find correct tier and progress
				for (int j = 0; j < 10; ++j)
				{
					int progress = atoi(Game::TableLookup(challengeTable, i, 6 + j * 2));
					if (!progress) break;

					maxState = j + 2;
					maxProgress = progress;
				}

				Command::Execute(Utils::String::VA("setPlayerData challengeState %s %d", challenge, maxState));
				Command::Execute(Utils::String::VA("setPlayerData challengeProgress %s %d", challenge, maxProgress));
			}
		}
	}

	Game::dvar_t* QuickPatch::Dvar_RegisterAspectRatioDvar(const char* dvarName, const char** /*valueList*/, int defaultIndex, unsigned __int16 flags, const char* description)
	{
		static const char* r_aspectRatioEnum[] =
		{
			"auto",
			"standard",
			"wide 16:10",
			"wide 16:9",
			"custom",
			nullptr
		};

		// register custom aspect ratio dvar
		QuickPatch::r_customAspectRatio = Dvar::Register<float>("r_customAspectRatio",
			16.0f / 9.0f, 4.0f / 3.0f, 63.0f / 9.0f, flags,
			"Screen aspect ratio. Divide the width by the height in order to get the aspect ratio value. For example: 16 / 9 = 1,77");

		// register enumeration dvar
		return Game::Dvar_RegisterEnum(dvarName, r_aspectRatioEnum, defaultIndex, flags, description);
	}

	void QuickPatch::SetAspectRatio()
	{
		// set the aspect ratio
		Utils::Hook::Set<float>(0x66E1C78, r_customAspectRatio.get<float>());
	}

	__declspec(naked) void QuickPatch::SetAspectRatio_Stub()
	{
		__asm
		{
			cmp eax, 4;
			ja goToDefaultCase;
			je useCustomRatio;

			// execute switch statement code
			push 0x5063FC;
			retn;

		goToDefaultCase:
			push 0x5064FC;
			retn;

		useCustomRatio:
			// set custom resolution
			pushad;
			call SetAspectRatio;
			popad;

			// set widescreen to 1
			mov eax, 1;

			// continue execution
			push 0x506495;
			retn;
		}
	}

	BOOL QuickPatch::IsDynClassname_Stub(const char* classname)
	{
		const auto version = Zones::Version();

		if (version >= VERSION_LATEST_CODO)
		{
			for (auto i = 0; i < Game::spawnVars->numSpawnVars; i++)
			{
				char** kvPair = Game::spawnVars->spawnVars[i];
				const auto* key = kvPair[0];
				const auto* val = kvPair[1];

				auto isSpecOps = std::strncmp(key, "script_specialops", 17) == 0;
				auto isSpecOpsOnly = (val[0] == '1') && (val[1] == '\0');

				if (isSpecOps && isSpecOpsOnly)
				{
					// This will prevent spawning of any entity that contains "script_specialops: '1'"
					// It removes extra hitboxes / meshes on 461+ CODO multiplayer maps
					return TRUE;
				}
			}
		}

		return Utils::Hook::Call<BOOL(const char*)>(0x444810)(classname); // IsDynClassname
	}

	void QuickPatch::CL_KeyEvent_OnEscape()
	{
		if (Game::Con_CancelAutoComplete())
		{
			return;
		}

		if (TextRenderer::HandleFontIconAutocompleteKey(0, TextRenderer::FONT_ICON_ACI_CONSOLE, Game::K_ESCAPE))
		{
			return;
		}

		// Close console
		Game::Key_RemoveCatcher(0, ~Game::KEYCATCH_CONSOLE);
	}

	__declspec(naked) void QuickPatch::CL_KeyEvent_ConsoleEscape_Stub()
	{
		__asm
		{
			pushad
			call CL_KeyEvent_OnEscape
			popad

			// Exit CL_KeyEvent function
			mov ebx, 0x4F66F2
			jmp ebx
		}
	}

	void QuickPatch::R_AddImageToList_Hk(Game::XAssetHeader header, void* data)
	{
		auto* imageList = static_cast<Game::ImageList*>(data);

		assert(imageList->count < ARRAYSIZE(imageList->image));

		if (header.image->texture.basemap)
		{
			imageList->image[imageList->count++] = header.image;
		}
	}

	void QuickPatch::Sys_SpawnQuitProcess_Hk()
	{
		if (*Game::sys_exitCmdLine[0] == '\0')
		{
			return;
		}

		const std::filesystem::path workingDir = std::filesystem::current_path();
		const std::wstring binary = Utils::String::Convert(*Game::sys_exitCmdLine);
		const std::wstring commandLine = std::format(L"\"{}\" iw4x --pass \"{}\"", (workingDir / binary).wstring(), Utils::GetLaunchParameters());

		SetEnvironmentVariableA("MW2_INSTALL", workingDir.string().data());
		Utils::Library::LaunchProcess(binary, commandLine, workingDir);
	}

	__declspec(naked) void QuickPatch::SND_GetAliasOffset_Stub()
	{
		using namespace Game;

		static const char* msg = "SND_GetAliasOffset: Could not find sound alias '%s'";
		using namespace Game;

		__asm
		{
			// Check if snd_alias_t* is null immediately after call to Com_FindSoundAlias_FastFile
			test eax, eax
			jz error

			// Game code hook skipped
			mov ecx, eax
			mov edx, dword ptr [ecx + 0x4]

			// Resume function
			push 0x437CB2
			ret

		error:
			add esp, 0x4 // Com_FindSoundAlias_FastFile takes one argument

			push [esi] // alias->aliasName
			push msg
			push ERR_DROP
			call Com_Error // Going to longjmp back to safety
			add esp, 0xC

			xor eax, eax
			pop esi
			ret
		}
	}

	Game::dvar_t* QuickPatch::Dvar_RegisterConMinicon(const char* dvarName, [[maybe_unused]] bool value, unsigned __int16 flags, const char* description)
	{
#ifdef _DEBUG
		constexpr auto value_ = true;
#else
		constexpr auto value_ = false;
#endif
		return Game::Dvar_RegisterBool(dvarName, value_, flags, description);
	}

	QuickPatch::QuickPatch()
	{
		// Filtering any mapents that is intended for Spec:Ops gamemode (CODO) and prevent them from spawning
		Utils::Hook(0x5FBD6E, QuickPatch::IsDynClassname_Stub, HOOK_CALL).install()->quick();

		// Hook escape handling on open console to change behaviour to close the console instead of only canceling autocomplete
		Utils::Hook(0x4F66A3, CL_KeyEvent_ConsoleEscape_Stub, HOOK_JUMP).install()->quick();

		// Intermission time dvar
		Game::Dvar_RegisterFloat("scr_intermissionTime", 10, 0, 120, Game::DVAR_NONE, "Time in seconds before match server loads the next map");

		// Add ultrawide support
		Utils::Hook(0x51B13B, QuickPatch::Dvar_RegisterAspectRatioDvar, HOOK_CALL).install()->quick();
		Utils::Hook(0x5063F3, QuickPatch::SetAspectRatio_Stub, HOOK_JUMP).install()->quick();

		Utils::Hook(0x4FA448, QuickPatch::Dvar_RegisterConMinicon, HOOK_CALL).install()->quick();

		Utils::Hook::Set<void(*)(Game::XAssetHeader, void*)>(0x51FCDD, QuickPatch::R_AddImageToList_Hk);

		Utils::Hook::Set<const char*>(0x41DB8C, "iw4x-sp.exe");
		Utils::Hook(0x4D6989, QuickPatch::Sys_SpawnQuitProcess_Hk, HOOK_CALL).install()->quick();

		// Fix crash as nullptr goes unchecked
		Utils::Hook(0x437CAD, QuickPatch::SND_GetAliasOffset_Stub, HOOK_JUMP).install()->quick();

		// remove system pre-init stuff (improper quit, disk full)
		Utils::Hook::Set<BYTE>(0x411350, 0xC3);

		// Don't delete config files if corrupted
		Utils::Hook::Set<BYTE>(0x47DCB3, 0xEB);
		Utils::Hook::Set<BYTE>(0x4402B6, 0);

		// hopefully allow alt-tab during game, used at least in alt-enter handling
		Utils::Hook::Set<DWORD>(0x45ACE0, 0xC301B0);

		// fs_basegame
		Utils::Hook::Set<const char*>(0x6431D1, BASEGAME);

		// window title
		Utils::Hook::Set<const char*>(0x5076A0, "IW4x: Multiplayer");

		// sv_hostname
		Utils::Hook::Set<const char*>(0x4D378B, "IW4Host");

		// console logo
		Utils::Hook::Set<const char*>(0x428A66, BASEGAME "/images/logo.bmp");

		// splash logo
		Utils::Hook::Set<const char*>(0x475F9E, BASEGAME "/images/splash.bmp");

		Utils::Hook::Set<const char*>(0x4876C6, "Successfully read stats data\n");

		// Numerical ping (cg_scoreboardPingText 1)
		Utils::Hook::Set<BYTE>(0x45888E, 1);
		Utils::Hook::Set<BYTE>(0x45888C, Game::DVAR_CHEAT);

		// increase font sizes for chat on higher resolutions
		static float float13 = 13.0f;
		static float float10 = 10.0f;
		Utils::Hook::Set<float*>(0x5814AE, &float13);
		Utils::Hook::Set<float*>(0x5814C8, &float10);

		// Enable commandline arguments
		Utils::Hook::Set<BYTE>(0x464AE4, 0xEB);

		// remove limit on IWD file loading
		Utils::Hook::Set<BYTE>(0x642BF3, 0xEB);

		// Fix stats sleeping
		Utils::Hook::Set<BYTE>(0x6832BA, 0xEB);
		Utils::Hook::Set<BYTE>(0x4BD190, 0xC3);

		// remove 'impure stats' checking
		Utils::Hook::Set<BYTE>(0x4BB250, 0x33);
		Utils::Hook::Set<BYTE>(0x4BB251, 0xC0);
		Utils::Hook::Set<DWORD>(0x4BB252, 0xC3909090);

		// default sv_pure to 0
		Utils::Hook::Set<BYTE>(0x4D3A74, 0);

		// remove activeAction execution (exploit in mods)
		Utils::Hook::Set<BYTE>(0x5A1D43, 0xEB);

		// disable bind protection
		Utils::Hook::Set<BYTE>(0x4DACA2, 0xEB);

		// require Windows 6 (Vista)
		Utils::Hook::Set<BYTE>(0x467ADF, 6);
		Utils::Hook::Set<char>(0x6DF5D6, '6');

		// disable 'ignoring asset' notices
		Utils::Hook::Nop(0x5BB902, 5);

		// disable migration_dvarErrors
		Utils::Hook::Set<BYTE>(0x60BDA7, 0);

		// allow joining 'developer 1' servers
		Utils::Hook::Set<BYTE>(0x478BA2, 0xEB);

		// fs_game fixes
		Utils::Hook::Nop(0x4A5D74, 2); // remove fs_game profiles
		Utils::Hook::Set<BYTE>(0x4081FD, 0xEB); // defaultweapon

		// filesystem init default_mp.cfg check
		Utils::Hook::Nop(0x461A9E, 5);
		Utils::Hook::Nop(0x461AAA, 5);
		Utils::Hook::Set<BYTE>(0x461AB4, 0xEB);

		// vid_restart when ingame
		Utils::Hook::Nop(0x4CA1FA, 6);

		// Filter log (initially com_logFilter, but I don't see why that dvar print is needed)
		// Seems like it's needed for B3, so there is a separate handling for dedicated servers in Dedicated.cpp
		if (!Dedicated::IsEnabled())
		{
			Utils::Hook::Nop(0x647466, 5); // 'dvar set' lines
			Utils::Hook::Nop(0x5DF4F2, 5); // 'sending splash open' lines
		}

		// intro stuff
		Utils::Hook::Nop(0x60BEE9, 5); // Don't show legals
		Utils::Hook::Nop(0x60BEF6, 5); // Don't reset the intro dvar
		Utils::Hook::Set<const char*>(0x60BED2, "unskippablecinematic IW_logo\n");
		Utils::Hook::Set<const char*>(0x51C2A4, "%s\\" BASEGAME "\\video\\%s.bik");
		Utils::Hook::Set<DWORD>(0x51C2C2, 0x78A0AC);

		// Redirect logs
		Utils::Hook::Set<const char*>(0x5E44D8, "logs/games_mp.log");
		Utils::Hook::Set<const char*>(0x60A90C, "logs/console_mp.log");
		Utils::Hook::Set<const char*>(0x60A918, "logs/console_mp.log");

		// Rename config
		Utils::Hook::Set<const char*>(0x461B4B, CLIENT_CONFIG);
		Utils::Hook::Set<const char*>(0x47DCBB, CLIENT_CONFIG);
		Utils::Hook::Set<const char*>(0x6098F8, CLIENT_CONFIG);
		Utils::Hook::Set<const char*>(0x60B279, CLIENT_CONFIG);
		Utils::Hook::Set<const char*>(0x60BBD4, CLIENT_CONFIG);

		// Disable profile system
//		Utils::Hook::Nop(0x60BEB1, 5); // GamerProfile_InitAllProfiles - Causes an error, when calling a harrier killstreak.
//		Utils::Hook::Nop(0x60BEB8, 5); // GamerProfile_LogInProfile
//		Utils::Hook::Nop(0x4059EA, 5); // GamerProfile_RegisterCommands
		Utils::Hook::Nop(0x4059EF, 5); // GamerProfile_RegisterDvars
		Utils::Hook::Nop(0x47DF9A, 5); // GamerProfile_UpdateSystemDvars
		Utils::Hook::Set<BYTE>(0x5AF0D0, 0xC3); // GamerProfile_SaveProfile
		Utils::Hook::Set<BYTE>(0x4E6870, 0xC3); // GamerProfile_UpdateSystemVarsFromProfile
		Utils::Hook::Set<BYTE>(0x4C37F0, 0xC3); // GamerProfile_UpdateProfileAndSaveIfNeeded
		Utils::Hook::Set<BYTE>(0x633CA0, 0xC3); // GamerProfile_SetPercentCompleteMP

		Utils::Hook::Nop(0x5AF1EC, 5); // Profile loading error
		Utils::Hook::Set<BYTE>(0x5AE212, 0xC3); // Profile reading

		// GamerProfile_RegisterCommands
		// Some random function used as nullsub :P
		Utils::Hook::Set<DWORD>(0x45B868, 0x5188FB); // profile_menuDvarsSetup
		Utils::Hook::Set<DWORD>(0x45B87E, 0x5188FB); // profile_menuDvarsFinish
		Utils::Hook::Set<DWORD>(0x45B894, 0x5188FB); // profile_toggleInvertedPitch
		Utils::Hook::Set<DWORD>(0x45B8AA, 0x5188FB); // profile_setViewSensitivity
		Utils::Hook::Set<DWORD>(0x45B8C3, 0x5188FB); // profile_setButtonsConfig
		Utils::Hook::Set<DWORD>(0x45B8D9, 0x5188FB); // profile_setSticksConfig
		Utils::Hook::Set<DWORD>(0x45B8EF, 0x5188FB); // profile_toggleAutoAim
		Utils::Hook::Set<DWORD>(0x45B905, 0x5188FB); // profile_SetHasEverPlayed_MainMenu
		Utils::Hook::Set<DWORD>(0x45B91E, 0x5188FB); // profile_SetHasEverPlayed_SP
		Utils::Hook::Set<DWORD>(0x45B934, 0x5188FB); // profile_SetHasEverPlayed_SO
		Utils::Hook::Set<DWORD>(0x45B94A, 0x5188FB); // profile_SetHasEverPlayed_MP
		Utils::Hook::Set<DWORD>(0x45B960, 0x5188FB); // profile_setVolume
		Utils::Hook::Set<DWORD>(0x45B979, 0x5188FB); // profile_setGamma
		Utils::Hook::Set<DWORD>(0x45B98F, 0x5188FB); // profile_setBlacklevel
		Utils::Hook::Set<DWORD>(0x45B9A5, 0x5188FB); // profile_toggleCanSkipOffensiveMissions

		// Patch SV_IsClientUsingOnlineStatsOffline
		Utils::Hook::Set<DWORD>(0x46B710, 0x90C3C033);

		// Fix mouse lag
		Utils::Hook::Nop(0x4731F5, 8);
		Scheduler::Loop([]
		{
			SetThreadExecutionState(ES_DISPLAY_REQUIRED);
		}, Scheduler::Pipeline::RENDERER);

		// Fix mouse pitch adjustments
		UIMousePitch = Dvar::Register<bool>("ui_mousePitch", false, Game::DVAR_ARCHIVE, "");
		UIScript::Add("updateui_mousePitch", []([[maybe_unused]] const UIScript::Token& token, [[maybe_unused]] const Game::uiInfo_s* info)
		{
			if (UIMousePitch.get<bool>())
			{
				Game::Dvar_SetFloatByName("m_pitch", -0.022f);
			}
			else
			{
				Game::Dvar_SetFloatByName("m_pitch", 0.022f);
			}
		});

		Command::Add("unlockstats", QuickPatch::UnlockStats);

		Command::Add("dumptechsets", [](const Command::Params* param)
		{
			if (param->size() != 2)
			{
				Logger::Print("usage: dumptechsets <fastfile> | all\n");
				return;
			}

			std::vector<std::string> fastFiles;
			if (std::strcmp(param->get(1), "all") == 0)
			{
				for (const auto& entry : Utils::IO::ListFiles("zone/english", false))
				{
					const auto& f = entry.path().string();
					fastFiles.emplace_back(f.substr(7, f.length() - 10));
				}

				for (const auto& entry : Utils::IO::ListFiles("zone/dlc", false))
				{
					const auto& f = entry.path().string();
					fastFiles.emplace_back(f.substr(3, f.length() - 6));
				}

				for (const auto& entry : Utils::IO::ListFiles("zone/patch", false))
				{
					const auto& f = entry.path().string();
					fastFiles.emplace_back(f.substr(5, f.length() - 8));
				}
			}
			else
			{
				fastFiles.emplace_back(param->get(1));
			}

			auto count = 0;

			AssetHandler::OnLoad([](Game::XAssetType type, Game::XAssetHeader asset, const std::string& name, bool* /*restrict*/)
			{
				// they're basically the same right?
				if (type == Game::ASSET_TYPE_PIXELSHADER || type == Game::ASSET_TYPE_VERTEXSHADER)
				{
					Utils::IO::CreateDir("userraw/shader_bin");

					const char* formatString;
					if (type == Game::ASSET_TYPE_PIXELSHADER)
					{
						formatString = "userraw/shader_bin/%.ps";
					}
					else
					{
						formatString = "userraw/shader_bin/%.vs";
					}

					const auto path = std::format("{}{}", formatString, name);
					if (Utils::IO::FileExists(path)) return;

					Utils::Stream buffer(0x1000);
					auto* dest = buffer.dest<Game::MaterialPixelShader>();
					buffer.save(asset.pixelShader);

					if (asset.pixelShader->prog.loadDef.program)
					{
						buffer.saveArray(asset.pixelShader->prog.loadDef.program, asset.pixelShader->prog.loadDef.programSize);
						Utils::Stream::ClearPointer(&dest->prog.loadDef.program);
					}

					Utils::IO::WriteFile(path, buffer.toBuffer());
				}

				if (type == Game::ASSET_TYPE_TECHNIQUE_SET)
				{
					Utils::IO::CreateDir("userraw/techsets");
					Utils::Stream buffer(0x1000);
					auto* dest = buffer.dest<Game::MaterialTechniqueSet>();
					buffer.save(asset.techniqueSet);

					if (asset.techniqueSet->name)
					{
						buffer.saveString(asset.techniqueSet->name);
						Utils::Stream::ClearPointer(&dest->name);
					}

					for (int i = 0; i < ARRAYSIZE(Game::MaterialTechniqueSet::techniques); ++i)
					{
						auto* technique = asset.techniqueSet->techniques[i];

						if (technique)
						{
							// Size-check is obsolete, as the structure is dynamic
							buffer.align(Utils::Stream::ALIGN_4);

							auto* destTechnique = buffer.dest<Game::MaterialTechnique>();
							buffer.save(technique, 8);

							// Save_MaterialPassArray
							auto* destPasses = buffer.dest<Game::MaterialPass>();
							buffer.saveArray(technique->passArray, technique->passCount);

							for (std::uint16_t j = 0; j < technique->passCount; ++j)
							{
								AssertSize(Game::MaterialPass, 20);

								Game::MaterialPass* destPass = &destPasses[j];
								Game::MaterialPass* pass = &technique->passArray[j];

								if (pass->vertexDecl)
								{

								}

								if (pass->args)
								{
									buffer.align(Utils::Stream::ALIGN_4);
									buffer.saveArray(pass->args, pass->perPrimArgCount + pass->perObjArgCount + pass->stableArgCount);
									Utils::Stream::ClearPointer(&destPass->args);
								}
							}

							if (technique->name)
							{
								buffer.saveString(technique->name);
								Utils::Stream::ClearPointer(&destTechnique->name);
							}

							Utils::Stream::ClearPointer(&dest->techniques[i]);
						}
					}
				}
			});

			for (const auto& fastFile : fastFiles)
			{
				if (!Game::DB_IsZoneLoaded(fastFile.data()))
				{
					Game::XZoneInfo info;
					info.name = fastFile.data();
					info.allocFlags = 0x20;
					info.freeFlags = 0;

					Game::DB_LoadXAssets(&info, 1, true);
				}

				// unload the fastfiles so we don't run out of memory or asset pools
				if (count % 5)
				{
					Game::XZoneInfo info;
					info.name = nullptr;
					info.allocFlags = 0x0;
					info.freeFlags = 0x20;
					Game::DB_LoadXAssets(&info, 1, true);
				}

				count++;
			}
		});

#ifdef DEBUG_MAT_LOG
		AssetHandler::OnLoad([](Game::XAssetType type, Game::XAssetHeader asset, const std::string& /*name*/, bool* /*restrict*/)
		{
			if (type == Game::XAssetType::ASSET_TYPE_GFXWORLD)
			{
				std::string buffer;

				for (unsigned int i = 0; i < asset.gfxWorld->dpvs.staticSurfaceCount; ++i)
				{
					buffer.append(Utils::String::VA("%s\n", asset.gfxWorld->dpvs.surfaces[asset.gfxWorld->dpvs.sortedSurfIndex[i]].material->info.name));
				}

				Utils::IO::WriteFile("userraw/logs/matlog.txt", buffer);
			}
		});
#endif

		// Debug patches
#ifdef DEBUG
		// ui_debugMode 1
		//Utils::Hook::Set<bool>(0x6312E0, true);

		// developer 2
		Utils::Hook::Set<BYTE>(0x4FA425, 2);
		Utils::Hook::Set<BYTE>(0x51B087, 2);
		Utils::Hook::Set<BYTE>(0x60AE13, 2);

		// developer_Script 1
		Utils::Hook::Set<bool>(0x60AE2B, true);

		// Disable cheat protection for dvars
		Utils::Hook::Set<BYTE>(0x646515, 0xEB); // Dvar_IsCheatProtected
#else
		// Remove missing tag message
		Utils::Hook::Nop(0x4EBF1A, 5);
#endif

		if (Flags::HasFlag("nointro"))
		{
			Utils::Hook::Set<BYTE>(0x60BECF, 0xEB);
		}
	}

	bool QuickPatch::unitTest()
	{
		uint32_t randIntCount = 4'000'000;
		Logger::Debug("Generating {} random integers...", randIntCount);

		const auto startTime = std::chrono::high_resolution_clock::now();

		for (uint32_t i = 0; i < randIntCount; ++i)
		{
			Utils::Cryptography::Rand::GenerateInt();
		}

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
		Logger::Debug("took {}ms", duration);

		Logger::Debug("Testing ZLib compression...");

		std::string test = Utils::String::VA("%c", Utils::Cryptography::Rand::GenerateInt());

		for (int i = 0; i < 21; ++i)
		{
			std::string compressed = Utils::Compression::ZLib::Compress(test);
			std::string decompressed = Utils::Compression::ZLib::Decompress(compressed);

			if (test != decompressed)
			{
				Logger::PrintError(Game::CON_CHANNEL_ERROR, "Compressing {} bytes and decompressing failed!\n", test.size());
				return false;
			}

			const auto size = test.size();
			for (unsigned int j = 0; j < size; ++j)
			{
				test.append(Utils::String::VA("%c", Utils::Cryptography::Rand::GenerateInt()));
			}
		}

		Logger::Debug("Success");

		Logger::Debug("Testing trimming...");
		std::string trim1 = " 1 ";
		std::string trim2 = "   1";
		std::string trim3 = "1   ";

		Utils::String::Trim(trim1);
		Utils::String::LTrim(trim2);
		Utils::String::RTrim(trim3);

		if (trim1 != "1") return false;
		if (trim2 != "1") return false;
		if (trim3 != "1") return false;

		Logger::Debug("Success");
		return true;
	}
}
