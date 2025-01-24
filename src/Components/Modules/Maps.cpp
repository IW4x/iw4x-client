
#include "ArenaLength.hpp"
#include "FastFiles.hpp"
#include "RawFiles.hpp"
#include "StartupMessages.hpp"
#include "Theatre.hpp"
#include "GSC/Script.hpp"

namespace Components
{
	Maps::UserMapContainer Maps::UserMap;
	std::string Maps::CurrentMainZone;
	std::vector<std::pair<std::string, std::string>> Maps::DependencyList;
	std::vector<std::string> Maps::CurrentDependencies;
	std::vector<std::string> Maps::FoundCustomMaps;

	Dvar::Var Maps::RListSModels;

	bool Maps::SPMap;
	std::vector<Maps::DLC> Maps::DlcPacks;

	const char* Maps::UserMapFiles[4] =
	{
		".ff",
		"_load.ff",
		".iwd",
		".arena",
	};

	Maps::UserMapContainer* Maps::GetUserMap()
	{
		return &Maps::UserMap;
	}

	void Maps::UserMapContainer::loadIwd()
	{
		if (this->isValid() && !this->searchPath.iwd)
		{
			auto iwdName = std::format("{}.iwd", this->mapname);
			auto path = std::format("{}\\usermaps\\{}\\{}", (*Game::fs_basepath)->current.string, this->mapname, iwdName);

			if (Utils::IO::FileExists(path))
			{
				this->searchPath.iwd = Game::FS_IsShippedIWD(path.data(), iwdName.data());

				if (this->searchPath.iwd)
				{
					this->searchPath.bLocalized = false;
					this->searchPath.ignore = 0;
					this->searchPath.ignorePureCheck = 0;
					this->searchPath.language = 0;
					this->searchPath.dir = nullptr;
					this->searchPath.next = *Game::fs_searchpaths;
					*Game::fs_searchpaths = &this->searchPath;
				}
			}
		}
	}

	void Maps::UserMapContainer::reloadIwd()
	{
		if (this->isValid() && this->wasFreed)
		{
			this->wasFreed = false;
			this->searchPath.iwd = nullptr;
			this->loadIwd();
		}
	}

	void Maps::UserMapContainer::handlePackfile(void* packfile)
	{
		if (this->isValid() && this->searchPath.iwd == packfile)
		{
			this->wasFreed = true;
		}
	}

	void Maps::UserMapContainer::freeIwd()
	{
		if (this->isValid() && this->searchPath.iwd && !this->wasFreed)
		{
			this->wasFreed = true;

			// Unchain our searchpath
			for (auto** pathPtr = Game::fs_searchpaths; *pathPtr; pathPtr = &(*pathPtr)->next)
			{
				if (*pathPtr == &this->searchPath)
				{
					*pathPtr = (*pathPtr)->next;
					break;
				}
			}

			Game::unzClose(this->searchPath.iwd->handle);

			// Use game's free function
			Utils::Hook::Call<void(void*)>(0x6B5CF2)(this->searchPath.iwd->buildBuffer);
			Utils::Hook::Call<void(void*)>(0x6B5CF2)(this->searchPath.iwd);

			ZeroMemory(&this->searchPath, sizeof(this->searchPath));
		}
	}

	const char* Maps::LoadArenaFileStub(const char* name, char* buffer, int size)
	{
		std::string  data;

		if (Maps::UserMap.isValid())
		{
			const auto mapname = Maps::UserMap.getName();
			const auto arena = GetArenaPath(mapname);

			if (Utils::IO::FileExists(arena))
			{
				// Replace all arenas with just this one
				data = Utils::IO::ReadFile(arena);
			}
		}
		else
		{
			data = RawFiles::ReadRawFile(name, buffer, size);
		}

		strncpy_s(buffer, size, data.data(), _TRUNCATE);
		return buffer;
	}

	void Maps::UnloadMapZones(Game::XZoneInfo* zoneInfo, unsigned int zoneCount, int sync)
	{
		Game::DB_LoadXAssets(zoneInfo, zoneCount, sync);

		if (Maps::UserMap.isValid())
		{
			Maps::UserMap.freeIwd();
			Maps::UserMap.clear();
		}
	}

	void Maps::LoadMapZones(Game::XZoneInfo* zoneInfo, unsigned int zoneCount, int sync)
	{
		if (!zoneInfo) return;

		Maps::SPMap = false;
		Maps::CurrentMainZone = zoneInfo->name;
		Maps::CurrentDependencies.clear();

		auto dependencies = GetDependenciesForMap(zoneInfo->name);

		std::vector<Game::XZoneInfo> data;
		Utils::Merge(&data, zoneInfo, zoneCount);
		Utils::Memory::Allocator allocator;

		if (dependencies.requiresTeamZones)
		{
			auto teams = dependencies.requiredTeams;

			Game::XZoneInfo team;
			team.allocFlags = zoneInfo->allocFlags;
			team.freeFlags = zoneInfo->freeFlags;

			team.name = allocator.duplicateString(std::format("iw4x_team_{}", teams.first));
			data.push_back(team);

			team.name = allocator.duplicateString(std::format("iw4x_team_{}", teams.second));
			data.push_back(team);
		}

		Utils::Merge(&Maps::CurrentDependencies, dependencies.requiredMaps.data(), dependencies.requiredMaps.size());
		for (unsigned int i = 0; i < Maps::CurrentDependencies.size(); ++i)
		{
			Game::XZoneInfo info;

			info.name = (&Maps::CurrentDependencies[i])->data();
			info.allocFlags = zoneInfo->allocFlags;
			info.freeFlags = zoneInfo->freeFlags;

			data.push_back(info);
		}

		// Load patch files
		auto patchZone = std::format("patch_{}", zoneInfo->name);
		if (FastFiles::Exists(patchZone))
		{
			data.push_back({ patchZone.data(), zoneInfo->allocFlags, zoneInfo->freeFlags });
		}

		return FastFiles::LoadLocalizeZones(data.data(), data.size(), sync);
	}

	void Maps::OverrideMapEnts(Game::MapEnts* ents)
	{
		auto callback = [](Game::XAssetHeader header, void* ents)
			{
				Game::MapEnts* mapEnts = reinterpret_cast<Game::MapEnts*>(ents);
				Game::clipMap_t* clipMap = header.clipMap;

				if (clipMap && mapEnts && !_stricmp(mapEnts->name, clipMap->name))
				{
					clipMap->mapEnts = mapEnts;
					//*Game::marMapEntsPtr = mapEnts;
					//Game::G_SpawnEntitiesFromString();
				}
			};

		// Internal doesn't lock the thread, as locking is impossible, due to executing this in the thread that holds the current lock
		Game::DB_EnumXAssets_Internal(Game::XAssetType::ASSET_TYPE_CLIPMAP_MP, callback, ents, true);
		Game::DB_EnumXAssets_Internal(Game::XAssetType::ASSET_TYPE_CLIPMAP_SP, callback, ents, true);
	}

	void Maps::LoadAssetRestrict(Game::XAssetType type, Game::XAssetHeader asset, const std::string& name, bool* restrict)
	{
		if (std::find(Maps::CurrentDependencies.begin(), Maps::CurrentDependencies.end(), FastFiles::Current()) != Maps::CurrentDependencies.end()) // Shipment is a special case
		{
			switch (type)
			{
			case Game::XAssetType::ASSET_TYPE_CLIPMAP_MP:
			case Game::XAssetType::ASSET_TYPE_CLIPMAP_SP:
			case Game::XAssetType::ASSET_TYPE_GAMEWORLD_SP:
			case Game::XAssetType::ASSET_TYPE_GAMEWORLD_MP:
			case Game::XAssetType::ASSET_TYPE_GFXWORLD:
			case Game::XAssetType::ASSET_TYPE_MAP_ENTS:
			case Game::XAssetType::ASSET_TYPE_COMWORLD:
			case Game::XAssetType::ASSET_TYPE_FXWORLD:
				*restrict = true;
				return;
			}
		}

		if (type == Game::XAssetType::ASSET_TYPE_ADDON_MAP_ENTS)
		{
			*restrict = true;
			return;
		}

		if (type == Game::XAssetType::ASSET_TYPE_WEAPON)
		{
			if ((!strstr(name.data(), "_mp") && name != "none" && name != "destructible_car") || Zones::Version() >= VERSION_ALPHA2)
			{
				*restrict = true;
				return;
			}
		}

		if (type == Game::XAssetType::ASSET_TYPE_STRINGTABLE)
		{
			if (FastFiles::Current() == "mp_cross_fire")
			{
				*restrict = true;
				return;
			}
		}

		if (type == Game::XAssetType::ASSET_TYPE_MAP_ENTS)
		{
			if (Flags::HasFlag("dump"))
			{
				Utils::IO::WriteFile(Utils::String::VA("raw/%s.ents", name.data()), asset.mapEnts->entityString, true);
			}

			static std::string mapEntities;
			FileSystem::File ents(name + ".ents", Game::FS_THREAD_DATABASE);
			if (ents.exists())
			{
				mapEntities = ents.getBuffer();
				asset.mapEnts->entityString = mapEntities.data();
				asset.mapEnts->numEntityChars = mapEntities.size() + 1;
			}
		}

		// This is broken
		if ((type == Game::XAssetType::ASSET_TYPE_MENU || type == Game::XAssetType::ASSET_TYPE_MENULIST) && Zones::Version() >= 359)
		{
			*restrict = true;
			return;
		}
	}

	Game::G_GlassData* Maps::GetWorldData()
	{
		Logger::Print("Waiting for database...\n");
		while (!Game::Sys_IsDatabaseReady()) std::this_thread::sleep_for(10ms);

		if (!Game::DB_XAssetPool[Game::XAssetType::ASSET_TYPE_GAMEWORLD_MP].gameWorldMp || !Game::DB_XAssetPool[Game::XAssetType::ASSET_TYPE_GAMEWORLD_MP].gameWorldMp->name ||
			!Game::DB_XAssetPool[Game::XAssetType::ASSET_TYPE_GAMEWORLD_MP].gameWorldMp->g_glassData || Maps::SPMap)
		{
			return Game::DB_XAssetPool[Game::XAssetType::ASSET_TYPE_GAMEWORLD_SP].gameWorldSp->g_glassData;
		}

		return Game::DB_XAssetPool[Game::XAssetType::ASSET_TYPE_GAMEWORLD_MP].gameWorldMp->g_glassData;
	}

	__declspec(naked) void Maps::GetWorldDataStub()
	{
		__asm
		{
			push eax
			pushad

			call Maps::GetWorldData

			mov[esp + 20h], eax
			popad
			pop eax

			retn
		}
	}

	void Maps::LoadRawSun()
	{
		Game::R_FlushSun();

		Game::GfxWorld* world = *reinterpret_cast<Game::GfxWorld**>(0x66DEE94);

		if (FileSystem::File(std::format("sun/{}.sun", Maps::CurrentMainZone)))
		{
			Game::R_LoadSunThroughDvars(Maps::CurrentMainZone.data(), &world->sun);
		}
	}

	void Maps::ForceRefreshArenas()
	{
		if (!FastFiles::Ready())
		{
			Logger::Print("Not refreshing arenas (fastfiles are not ready yet)\n");
			return;
		}

		if (Game::Sys_IsMainThread())
		{
			if (*Game::g_quitRequested)
			{
				// No need to refresh if we're exiting the game
				return;
			}

			Game::sharedUiInfo_t* uiInfo = reinterpret_cast<Game::sharedUiInfo_t*>(0x62E4B78);
			uiInfo->updateArenas = 1;
			Game::UI_UpdateArenas();
		}
		else
		{
			// Dangerous!!
			assert(false && "Arenas refreshed from wrong thread??");
			Logger::Print("Tried to refresh arenas from a thread that is NOT the main thread!! This could have lead to a crash. Please report this bug and how you got it!");
		}
	}

	// TODO : Remove hook entirely?
	void Maps::GetBSPName(char* buffer, size_t size, const char* format, const char* mapname)
	{
		if (!Utils::String::StartsWith(mapname, "mp_") && !Utils::String::StartsWith(mapname, "zm_"))
		{
			format = "maps/%s.d3dbsp";
		}

		_snprintf_s(buffer, size, _TRUNCATE, format, mapname);
	}

	void Maps::HandleAsSPMap()
	{
		Maps::SPMap = true;
	}

	int Maps::IgnoreEntityStub(const char* entity)
	{
		return (Utils::String::StartsWith(entity, "dyn_") || Utils::String::StartsWith(entity, "node_") || Utils::String::StartsWith(entity, "actor_"));
	}

	std::unordered_map<std::string, std::string> Maps::ParseCustomMapArena(const std::string& singleMapArena)
	{
		static const std::regex regex("  (\\w*) *\"?((?:\\w| )*)\"?");
		std::unordered_map<std::string, std::string> arena;

		std::smatch m;

		std::string::const_iterator search_start(singleMapArena.cbegin());

		while (std::regex_search(search_start, singleMapArena.cend(), m, regex))
		{
			if (m.size() > 2)
			{
				arena.emplace(m[1].str(), m[2].str());
				search_start = m.suffix().first;
			}
		}

		return arena;
	}

	Maps::MapDependencies Maps::GetDependenciesForMap(const std::string& map)
	{
		std::string teamAxis = "opforce_composite";
		std::string teamAllies = "us_army";

		Maps::MapDependencies dependencies;

		// True by default - cause some maps won't have an arenafile entry
		dependencies.requiresTeamZones = true;

		for (int i = 0; i < *Game::arenaCount; ++i)
		{
			Game::newMapArena_t* arena = &ArenaLength::NewArenas[i];
			if (arena->mapName == map)
			{
				// If it's in the arena file, surely it's a vanilla map that doesn't need teams...
				dependencies.requiresTeamZones = false;

				for (std::size_t j = 0; j < std::extent_v<decltype(Game::newMapArena_t::keys)>; ++j)
				{
					const auto* key = arena->keys[j];
					const auto* value = arena->values[j];
					if (key == "dependency"s)
					{
						dependencies.requiredMaps = Utils::String::Split(arena->values[j], ' ');
					}
					else if (key == "allieschar"s)
					{
						teamAllies = value;
					}
					else if (key == "axischar"s)
					{
						teamAxis = value;
					}
					else if (key == "useteamzones"s)
					{
						// ... unless it specifies so!  This allows loading of CODO/COD4 zones that might not have the correct teams
						dependencies.requiresTeamZones = Utils::String::ToLower(value) == "true"s;
					}
				}

				break;
			}
		}

		dependencies.requiredTeams = std::make_pair(teamAllies, teamAxis);

		return dependencies;
	}

	void Maps::PrepareUsermap(const char* mapname)
	{
		if (Maps::UserMap.isValid())
		{
			Maps::UserMap.freeIwd();
			Maps::UserMap.clear();
		}

		if (Maps::IsUserMap(mapname))
		{
			Maps::UserMap = Maps::UserMapContainer(mapname);
			Maps::UserMap.loadIwd();
		}
		else
		{
			Maps::UserMap.clear();
		}
	}

	unsigned int Maps::GetUsermapHash(const std::string& map)
	{
		if (Utils::IO::DirectoryExists(std::format("usermaps/{}", map)))
		{
			std::string hash;

			for (std::size_t i = 0; i < ARRAYSIZE(Maps::UserMapFiles); ++i)
			{
				auto filePath = std::format("usermaps/{}/{}{}", map, map, Maps::UserMapFiles[i]);
				if (Utils::IO::FileExists(filePath))
				{
					hash.append(Utils::Cryptography::SHA256::Compute(Utils::IO::ReadFile(filePath)));
				}
			}

			return Utils::Cryptography::JenkinsOneAtATime::Compute(hash);
		}

		return 0;
	}

	void Maps::LoadNewMapCommand(char* buffer, size_t size, const char* /*format*/, const char* mapname, const char* gametype)
	{
		unsigned int hash = Maps::GetUsermapHash(mapname);
		_snprintf_s(buffer, size, _TRUNCATE, "loadingnewmap\n%s\n%s\n%d", mapname, gametype, hash);
	}

	int Maps::TriggerReconnectForMap(Game::msg_t* msg, const char* mapname)
	{
		Theatre::StopRecording();

		char hashBuf[100] = { 0 };
		unsigned int hash = atoi(Game::MSG_ReadStringLine(msg, hashBuf, sizeof(hashBuf)));

		if (!Maps::CheckMapInstalled(mapname, false, true) || hash && hash != Maps::GetUsermapHash(mapname))
		{
			// Reconnecting forces the client to download the new map
			Command::Execute("disconnect", false);
			Command::Execute("awaitDatabase", false); // Wait for the database to load
			Command::Execute("wait 100", false);
			Command::Execute("openmenu popup_reconnectingtoparty", false);
			Command::Execute("delayReconnect", false);
			return true;
		}

		return false;
	}

	__declspec(naked) void Maps::RotateCheckStub()
	{
		__asm
		{
			push eax
			pushad

			push[esp + 28h]
			push ebp
			call Maps::TriggerReconnectForMap
			add esp, 8h

			mov[esp + 20h], eax

			popad
			pop eax

			test eax, eax
			jnz skipRotation

			push 487C50h // Rotate map

			skipRotation :
			retn
		}
	}

	__declspec(naked) void Maps::SpawnServerStub()
	{
		__asm
		{
			pushad

			push[esp + 24h]
			call Maps::PrepareUsermap
			pop eax

			popad

			push 4A7120h // SV_SpawnServer
			retn
		}
	}

	__declspec(naked) void Maps::LoadMapLoadscreenStub()
	{
		__asm
		{
			pushad

			push[esp + 24h]
			call Maps::PrepareUsermap
			pop eax

			popad

			push 4D8030h // LoadMapLoadscreen
			retn
		}
	}

	void Maps::AddDlc(Maps::DLC dlc)
	{
		for (auto& pack : Maps::DlcPacks)
		{
			if (pack.index == dlc.index)
			{
				pack.maps = dlc.maps;
				Maps::UpdateDlcStatus();
				return;
			}
		}

		Dvar::Register<bool>(Utils::String::VA("isDlcInstalled_%d", dlc.index), false, Game::DVAR_EXTERNAL | Game::DVAR_INIT, "");

		Maps::DlcPacks.push_back(dlc);
		Maps::UpdateDlcStatus();
	}

	void Maps::UpdateDlcStatus()
	{
		bool hasAllDlcs = true;
		std::vector<bool> hasDlc;
		for (auto& pack : Maps::DlcPacks)
		{
			bool hasAllMaps = true;
			for (auto map : pack.maps)
			{
				if (!FastFiles::Exists(map))
				{
					hasAllMaps = false;
					hasAllDlcs = false;
					break;
				}
			}

			hasDlc.push_back(hasAllMaps);
			Dvar::Var(Utils::String::VA("isDlcInstalled_%d", pack.index)).set(hasAllMaps ? true : false);
		}

		// Must have all of dlc 3 to 5 or it causes issues
		static bool sentMessage = false;
		if (hasDlc.size() >= 5 && (hasDlc[2] || hasDlc[3] || hasDlc[4]) && (!hasDlc[2] || !hasDlc[3] || !hasDlc[4]) && !sentMessage)
		{
			StartupMessages::AddMessage("Warning:\n You only have some of DLCs 3-5 which are all required to be installed to work. There may be issues with those maps.");
			sentMessage = true;
		}

		Dvar::Var("isDlcInstalled_All").set(hasAllDlcs ? true : false);
	}

	bool Maps::IsCustomMap()
	{
		Game::GfxWorld*& gameWorld = *reinterpret_cast<Game::GfxWorld**>(0x66DEE94);
		if (gameWorld) return (gameWorld->checksum & 0xFFFF0000) == 0xC0D40000;
		return false;
	}

	bool Maps::IsUserMap(const std::string& mapname)
	{
		return Utils::IO::DirectoryExists(std::format("usermaps/{}", mapname)) && Utils::IO::FileExists(std::format("usermaps/{}/{}.ff", mapname, mapname));
	}

	void Maps::ScanCustomMaps()
	{
		FoundCustomMaps.clear();
		Logger::Print("Looking for custom maps...\n");

		std::filesystem::path basePath = (*Game::fs_basepath)->current.string;
		basePath /= "usermaps";

		if (!std::filesystem::exists(basePath))
		{
			return;
		}

		const auto entries = Utils::IO::ListFiles(basePath);

		for (const auto& entry : entries)
		{
			if (entry.is_directory())
			{
				const auto zoneName = entry.path().filename().string();
				const auto mapPath = std::format("{}\\{}.ff", entry.path().string(), zoneName);
				if (Utils::IO::FileExists(mapPath))
				{
					FoundCustomMaps.push_back(zoneName);
					Logger::Print("Discovered custom map {}\n", zoneName);
				}
			}
		}
	}

	std::string Maps::GetArenaPath(const std::string& mapName)
	{
		return std::format("usermaps/{}/{}.arena", mapName, mapName);
	}

	const std::vector<std::string>& Maps::GetCustomMaps()
	{
		return FoundCustomMaps;
	}

	Game::XAssetEntry* Maps::GetAssetEntryPool()
	{
		return *reinterpret_cast<Game::XAssetEntry**>(0x48E6F4);
	}

	// dlcIsTrue serves as a check if the map is a custom map and if it's missing
	bool Maps::CheckMapInstalled(const std::string& mapname, bool error, bool dlcIsTrue)
	{
		if (FastFiles::Exists(mapname)) return true;

		for (auto& pack : Maps::DlcPacks)
		{
			for (auto map : pack.maps)
			{
				if (map == mapname)
				{
					if (error)
					{
						Logger::Error(Game::ERR_DISCONNECT, "Missing DLC pack {} ({}) containing map {} ({}).\nPlease download it to play this map.",
							pack.name, pack.index, Localization::LocalizeMapName(mapname.data()), mapname);
					}

					return dlcIsTrue;
				}
			}
		}

		if (error)
		{
			Logger::Error(Game::ERR_DISCONNECT,
				"Missing map file {}.\nYou may have a damaged installation or are attempting to load a non-existent map.", mapname);
		}

		return false;
	}

	void Maps::HideModel()
	{
		Game::GfxWorld*& gameWorld = *reinterpret_cast<Game::GfxWorld**>(0x66DEE94);
		if (!gameWorld) return;

		std::string model = Dvar::Var("r_hideModel").get<std::string>();
		if (model.empty()) return;

		for (unsigned int i = 0; i < gameWorld->dpvs.smodelCount; ++i)
		{
			if (model == "all"s || gameWorld->dpvs.smodelDrawInsts[i].model->name == model)
			{
				gameWorld->dpvs.smodelVisData[0][i] = 0;
				gameWorld->dpvs.smodelVisData[1][i] = 0;
				gameWorld->dpvs.smodelVisData[2][i] = 0;
			}
		}
	}

	__declspec(naked) void Maps::HideModelStub()
	{
		__asm
		{
			pushad
			call Maps::HideModel
			popad

			push 541E40h
			retn
		}
	}

	void Maps::G_SpawnTurretHook(Game::gentity_s* ent, int unk, int unk2)
	{
		if (Maps::CurrentMainZone == "mp_backlot_sh"s || Maps::CurrentMainZone == "mp_con_spring"s ||
			Maps::CurrentMainZone == "mp_mogadishu_sh"s || Maps::CurrentMainZone == "mp_nightshift_sh"s)
		{
			return;
		}

		Utils::Hook::Call<void(Game::gentity_s*, int, int)>(0x408910)(ent, unk, unk2);
	}

	bool Maps::SV_SetTriggerModelHook(Game::gentity_s* ent) {

		// Use me for debugging
		//std::string classname = Game::SL_ConvertToString(ent->script_classname);
		//std::string targetname = Game::SL_ConvertToString(ent->targetname);

		return Utils::Hook::Call<bool(Game::gentity_s*)>(0x5050C0)(ent);
	}

	unsigned short Maps::CM_TriggerModelBounds_Hk(unsigned int triggerIndex, Game::Bounds* bounds)
	{

		auto* ents = *reinterpret_cast<Game::MapEnts**>(0x1AA651C);  // Use me for debugging

		if (ents)
		{
			if (triggerIndex >= ents->trigger.count)
			{
				Logger::Error(Game::errorParm_t::ERR_DROP, "Invalid trigger index ({}) in entities exceeds the maximum trigger count ({}) defined in the clipmap. Check your map ents, or your clipmap!", triggerIndex, ents->trigger.count);
				return 0;
			}
			else
			{
				return Utils::Hook::Call<unsigned short(int, Game::Bounds*)>(0x4416C0)(triggerIndex, bounds);
			}
		}

		return 0;
	}

	void Maps::GSCr_GetMapArenaInfo()
	{
		if (Game::Scr_GetNumParam() != 2)
		{
			Game::Scr_Error("GetMapArenaInfo: Needs az map name and a field name!");
			return;
		}

		const std::string mapName = Game::SL_ConvertToString(Game::Scr_GetConstString(0));
		const std::string fieldName = Game::SL_ConvertToString(Game::Scr_GetConstString(1));

		Game::UI_UpdateArenas();
		for (int i = 0; i < *Game::arenaCount; ++i)
		{
			Game::newMapArena_t* arena = &ArenaLength::NewArenas[i];
			if (arena->mapName == mapName)
			{
				// Found the map!
				for (std::size_t j = 0; j < std::extent_v<decltype(Game::newMapArena_t::keys)>; ++j)
				{
					const auto* key = arena->keys[j];
					const auto* value = arena->values[j];

					// Foudn the field!
					if (key == fieldName)
					{
						Game::Scr_AddString(value);
						return;
					}
				}

				const std::string error = std::format("Could not find field {} in arena entry for map {}!\n", fieldName, mapName);
				Game::Scr_Error(error.data());
				return;
			}
		}

		const std::string error = std::format("Map {} has no arena entry!\n", mapName);
		Game::Scr_Error(error.data());
	}

	void Maps::GSCr_GetMapList()
	{
		Game::Scr_MakeArray();

		Game::UI_UpdateArenas();
		for (int i = 0; i < *Game::arenaCount; ++i)
		{
			Game::newMapArena_t* arena = &ArenaLength::NewArenas[i];
			Game::Scr_AddString(arena->mapName);
			Game::Scr_AddArray();
		}
	}

	Maps::Maps()
	{
		Scheduler::Once([]
			{
				Dvar::Register<bool>("isDlcInstalled_All", false, Game::DVAR_EXTERNAL | Game::DVAR_INIT, "");
				Maps::RListSModels = Dvar::Register<bool>("r_listSModels", false, Game::DVAR_NONE, "Display a list of visible SModels");

				Maps::AddDlc({ 1, "Stimulus Pack", {"mp_complex", "mp_compact", "mp_storm", "mp_overgrown", "mp_crash"} });
				Maps::AddDlc({ 2, "Resurgence Pack", {"mp_abandon", "mp_vacant", "mp_trailerpark", "mp_strike", "mp_fuel2"} });
				Maps::AddDlc({ 3, "IW4x Classics", {"mp_nuked", "mp_cross_fire", "mp_cargoship", "mp_bloc", "mp_killhouse", "mp_bog_sh", "mp_cargoship_sh", "mp_shipment", "mp_shipment_long", "mp_rust_long", "mp_firingrange", "mp_bloc_sh", "mp_crash_tropical", "mp_estate_tropical", "mp_fav_tropical", "mp_storm_spring"} });
				Maps::AddDlc({ 4, "Call Of Duty 4 Pack", {"mp_farm", "mp_backlot", "mp_pipeline", "mp_countdown", "mp_crash_snow", "mp_carentan", "mp_broadcast", "mp_showdown", "mp_convoy", "mp_citystreets"} });
				Maps::AddDlc({ 5, "Modern Warfare 3 Pack", {"mp_dome", "mp_hardhat", "mp_paris", "mp_seatown", "mp_bravo", "mp_underground", "mp_plaza2", "mp_village", "mp_alpha"} });

				Maps::UpdateDlcStatus();

				UIScript::Add("downloadDLC", []([[maybe_unused]] const UIScript::Token& token, [[maybe_unused]] const Game::uiInfo_s* info)
					{
						const auto dlc = token.get<int>();

						Game::ShowMessageBox(Utils::String::VA("DLC %d does not exist!", dlc), "ERROR");
					});
			}, Scheduler::Pipeline::MAIN);

		// disable turrets on CoD:OL 448+ maps for now
		Utils::Hook(0x5EE577, Maps::G_SpawnTurretHook, HOOK_CALL).install()->quick();
		Utils::Hook(0x44A4D5, Maps::G_SpawnTurretHook, HOOK_CALL).install()->quick();

		// Catch trigger errors before they're critical
		Utils::Hook(0x5050D4, Maps::CM_TriggerModelBounds_Hk, HOOK_CALL).install()->quick();

#ifdef DEBUG
		// Check trigger models
		Utils::Hook(0x5FC0F1, Maps::SV_SetTriggerModelHook, HOOK_CALL).install()->quick();
		Utils::Hook(0x5FC2671, Maps::SV_SetTriggerModelHook, HOOK_CALL).install()->quick();
#endif

		//

//#define SORT_SMODELS
#if !defined(DEBUG) || !defined(SORT_SMODELS)
		// Don't sort static models
		Utils::Hook::Nop(0x53D815, 2);
#endif

		// Don't draw smodels
		//Utils::Hook::Set<BYTE>(0x541E40, 0xC3);

		// Restrict asset loading
		AssetHandler::OnLoad(Maps::LoadAssetRestrict);

		// hunk size (was 300 MiB)
		Utils::Hook::Set<DWORD>(0x64A029, 0x1C200000); // 450 MiB
		Utils::Hook::Set<DWORD>(0x64A057, 0x1C200000);

		// Intercept BSP name resolving
		Utils::Hook(0x4C5979, Maps::GetBSPName, HOOK_CALL).install()->quick();

		// Intercept map zone loading/unloading
		Utils::Hook(0x42C2AF, Maps::LoadMapZones, HOOK_CALL).install()->quick();
		Utils::Hook(0x60B477, Maps::UnloadMapZones, HOOK_CALL).install()->quick();

		// Ignore SP entities
		Utils::Hook(0x444810, Maps::IgnoreEntityStub, HOOK_JUMP).install()->quick();

		// WorldData pointer replacement
		Utils::Hook(0x4D90B6, Maps::GetWorldDataStub, HOOK_CALL).install()->quick();

		// Allow loading raw suns
		Utils::Hook(0x51B46A, Maps::LoadRawSun, HOOK_CALL).install()->quick();

		// Intercept map loading for usermap initialization
		Utils::Hook(0x6245E3, Maps::SpawnServerStub, HOOK_CALL).install()->quick();
		Utils::Hook(0x62493E, Maps::SpawnServerStub, HOOK_CALL).install()->quick();
		Utils::Hook(0x42CF58, Maps::LoadMapLoadscreenStub, HOOK_CALL).install()->quick();
		Utils::Hook(0x487CDD, Maps::LoadMapLoadscreenStub, HOOK_CALL).install()->quick();
		Utils::Hook(0x4CA3E9, Maps::LoadMapLoadscreenStub, HOOK_CALL).install()->quick();
		Utils::Hook(0x5A9D51, Maps::LoadMapLoadscreenStub, HOOK_CALL).install()->quick();
		Utils::Hook(0x5B34DD, Maps::LoadMapLoadscreenStub, HOOK_CALL).install()->quick();

		Command::Add("delayReconnect", []()
			{
				Scheduler::Once([]
					{
						Command::Execute("closemenu popup_reconnectingtoparty", false);
						Command::Execute("reconnect", false);
					}, Scheduler::Pipeline::CLIENT, 10s);
			});

		if (Dedicated::IsEnabled())
		{
			Utils::Hook(0x4A7251, Maps::LoadNewMapCommand, HOOK_CALL).install()->quick();
		}

		// Download the map before a map rotation if necessary
		// Conflicts with Theater's SV map rotation check, but this one is safer!
		Utils::Hook(0x5AA91C, Maps::RotateCheckStub, HOOK_CALL).install()->quick();

		// Load usermap arena file
		Utils::Hook(0x630A88, Maps::LoadArenaFileStub, HOOK_CALL).install()->quick();

		// Allow hiding specific smodels
		Utils::Hook(0x50E67C, Maps::HideModelStub, HOOK_CALL).install()->quick();

		// gsc: GetMapList()
		Components::GSC::Script::AddFunction(
			"GetMapList",
			GSCr_GetMapList
		);

		// gsc: GetMapArenaInfo(mapName, fieldName)
		Components::GSC::Script::AddFunction(
			"GetMapArenaInfo",
			GSCr_GetMapArenaInfo 
		);

		if (Dedicated::IsEnabled() || ZoneBuilder::IsEnabled())
		{
			return;
		}

		// Client only
		Scheduler::Loop([]
			{
				auto*& gameWorld = *reinterpret_cast<Game::GfxWorld**>(0x66DEE94);
				if (!Game::CL_IsCgameInitialized() || !gameWorld || !Maps::RListSModels.get<bool>()) return;

				std::map<std::string, int> models;
				for (unsigned int i = 0; i < gameWorld->dpvs.smodelCount; ++i)
				{
					if (gameWorld->dpvs.smodelVisData[0][i])
					{
						std::string name = gameWorld->dpvs.smodelDrawInsts[i].model->name;

						if (!models.contains(name)) models[name] = 1;
						else models[name]++;
					}
				}

				Game::Font_s* font = Game::R_RegisterFont("fonts/smallFont", 0);
				auto height = Game::R_TextHeight(font);
				auto scale = 0.75f;
				float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

				unsigned int i = 0;
				for (auto& model : models)
				{
					Game::R_AddCmdDrawText(Utils::String::VA("%d %s", model.second, model.first.data()), std::numeric_limits<int>::max(), font, 15.0f, (height * scale + 1) * (i++ + 1) + 15.0f, scale, scale, 0.0f, color, Game::ITEM_TEXTSTYLE_NORMAL);
				}
			}, Scheduler::Pipeline::RENDERER);
	}

	Maps::~Maps()
	{
		Maps::DlcPacks.clear();
		Maps::DependencyList.clear();
		Maps::CurrentMainZone.clear();
		Maps::CurrentDependencies.clear();
	}
}
