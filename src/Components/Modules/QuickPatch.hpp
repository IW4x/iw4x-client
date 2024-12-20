#pragma once

namespace Components
{
	class QuickPatch : public Component
	{
	public:
		QuickPatch();

		bool unitTest() override;

		static void UnlockStats();

	private:
		static Dvar::Var UIMousePitch;

		static Dvar::Var r_customAspectRatio;
		static Game::dvar_t* Dvar_RegisterAspectRatioDvar(const char* dvarName, const char** valueList, int defaultIndex, unsigned __int16 flags, const char* description);
		static void SetAspectRatio_Stub();
		static void SetAspectRatio();

		static BOOL IsDynClassname_Stub(const char* classname);

		static void CL_KeyEvent_OnEscape();
		static void CL_KeyEvent_ConsoleEscape_Stub();

		static void R_AddImageToList_Hk(Game::XAssetHeader header, void* data);

		static void Sys_SpawnQuitProcess_Hk();

		static void SND_GetAliasOffset_Stub();

		static Game::dvar_t* Dvar_RegisterConMinicon(const char* dvarName, bool value, unsigned __int16 flags, const char* description);
	};
}
