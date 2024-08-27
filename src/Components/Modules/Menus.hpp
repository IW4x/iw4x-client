#pragma once

#undef LoadOverrideForNativeMenu

namespace Components
{
	class Menus : public Component
	{
	public:
		Menus();

		static void Add(const std::string& menu);

		static std::vector<std::pair<bool, Game::menuDef_t*>> LoadOverrideForNativeMenu(Game::menuDef_t* menudef);
		static std::vector<std::pair<bool, Game::menuDef_t*>> LoadScriptMenuFromFile(const std::string& menu);
		static Game::menuDef_t* GetMenu(const std::string& name);
		
	private:
		static std::unordered_map<std::string, Game::menuDef_t*> MenuList;
		static std::unordered_map<std::string, Game::MenuList*> MenuListList;
		static std::vector<std::string> CustomMenus;

		static Game::XAssetHeader MenuFindHook(Game::XAssetType type, const std::string& filename);
		static Game::XAssetHeader MenuListFindHook(Game::XAssetType type, const std::string& filename);

		static Game::MenuList* LoadMenuList(Game::MenuList* menuList);
		static Game::MenuList* LoadScriptMenu(const char* menu);

		static void SafeMergeMenus(std::vector<std::pair<bool, Game::menuDef_t*>>* menus, std::vector<std::pair<bool, Game::menuDef_t*>> newMenus);

		static Game::script_s* LoadMenuScript(const std::string& name, const std::string& buffer);
		static int LoadMenuSource(const std::string& name, const std::string& buffer);

		static int ReserveSourceHandle();
		static bool IsValidSourceHandle(int handle);

		static Game::menuDef_t* ParseMenu(int handle);

		static void FreeScript(Game::script_s* script);
		static void FreeMenuSource(int handle);

		static void FreeMenuList(Game::MenuList* menuList);
		static void Menu_FreeItemMemory(Game::itemDef_s* item);
		static void FreeMenu(Game::menuDef_t* menudef);

		static void RemoveMenu(const std::string& menu);
		static void RemoveMenu(Game::menuDef_t* menudef);
		static void RemoveMenuList(const std::string& menuList);
		static void RemoveMenuList(Game::MenuList* menuList);

		static void OverrideMenu(Game::menuDef_t* menu);

		static bool IsMenuVisible(Game::UiContext* dc, Game::menuDef_t* menu);

		static void RemoveMenuFromContext(Game::UiContext* dc, Game::menuDef_t* menu);
	};
}
