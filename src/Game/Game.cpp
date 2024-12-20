#include <STDInclude.hpp>

namespace Game
{
	G_LogPrintf_t G_LogPrintf = G_LogPrintf_t(0x4B0150);
	G_GetWeaponIndexForName_t G_GetWeaponIndexForName = G_GetWeaponIndexForName_t(0x49E540);
	G_SpawnEntitiesFromString_t G_SpawnEntitiesFromString = G_SpawnEntitiesFromString_t(0x4D8840);
	G_Spawn_t G_Spawn = G_Spawn_t(0x4226F0);
	G_FreeEntity_t G_FreeEntity = G_FreeEntity_t(0x44C9D0);
	G_SpawnItem_t G_SpawnItem = G_SpawnItem_t(0x403770);
	G_TempEntity_t G_TempEntity = G_TempEntity_t(0x4511F0);
	G_AddEvent_t G_AddEvent = G_AddEvent_t(0x469A50);
	G_GetItemClassname_t G_GetItemClassname = G_GetItemClassname_t(0x492630);
	G_PrintEntities_t G_PrintEntities = G_PrintEntities_t(0x4E6A50);
	G_GetEntityTypeName_t G_GetEntityTypeName = G_GetEntityTypeName_t(0x4EB810);

	G_LocalizedStringIndex_t G_LocalizedStringIndex = G_LocalizedStringIndex_t(0x4582F0);

	G_DebugLineWithDuration_t G_DebugLineWithDuration = G_DebugLineWithDuration_t(0x4C3280);

	gentity_s* g_entities = reinterpret_cast<gentity_s*>(0x18835D8);
	unsigned short* PartName_None = reinterpret_cast<unsigned short*>(0x1AA2E7A); // result of GScr_AllocString("none");
	bool* g_quitRequested = reinterpret_cast<bool*>(0x649FB61);

	NetField* clientStateFields = reinterpret_cast<Game::NetField*>(0x741E40);
	size_t clientStateFieldsCount = Utils::Hook::Get<size_t>(0x7433C8);

	MssLocal* milesGlobal = reinterpret_cast<MssLocal*>(0x649A1A0);

	WinVars_t* g_wv = reinterpret_cast<WinVars_t*>(0x64A3AC8);

	const char* origErrorMsg = reinterpret_cast<const char*>(0x79B124);

	XModel* G_GetModel(const int index)
	{
		assert(index > 0);
		assert(index < MAX_MODELS);
		return cached_models[index];
	}

	void G_DebugStar(const float* point, const float* color)
	{
		CL_AddDebugStar(point, color, 20, 1);
	}
}
