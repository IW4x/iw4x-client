#include <STDInclude.hpp>
#include "Party.hpp"

#define MAX_SOURCEFILES	64
#define DEFINEHASHSIZE 1024

namespace Components
{
	std::vector<std::string> Menus::CustomMenus;
	std::unordered_map<std::string, Game::menuDef_t*> Menus::MenuList;
	std::unordered_map<std::string, Game::MenuList*> Menus::MenuListList;

	Game::KeywordHashEntry<Game::menuDef_t, 128, 3523>** menuParseKeywordHash;

	template <int HASH_COUNT, int HASH_SEED>
	static int KeywordHashKey(const char* keyword)
	{
		auto hash = 0;
		for (auto i = 0; keyword[i]; ++i)
		{
			hash += (i + HASH_SEED) * std::tolower(static_cast<unsigned char>(keyword[i]));
		}
		return (hash + (hash >> 8)) & (128 - 1);
	}

	template <typename T, int N, int M>
	static Game::KeywordHashEntry<T, N, M>* KeywordHashFind(Game::KeywordHashEntry<T, N, M>** table, const char* keyword)
	{
		auto hash = KeywordHashKey<N, M>(keyword);
		Game::KeywordHashEntry<T, N, M>* key = table[hash];
		if (key && !_stricmp(key->keyword, keyword))
		{
			return key;
		}
		return nullptr;
	}

	int Menus::ReserveSourceHandle()
	{
		// Check if a free slot is available
		auto i = 1;
		while (i < MAX_SOURCEFILES)
		{
			if (!Game::sourceFiles[i])
			{
				break;
			}

			++i;
		}

		if (i >= MAX_SOURCEFILES)
		{
			return 0;
		}

		// Reserve it, if yes
		Game::sourceFiles[i] = reinterpret_cast<Game::source_s*>(1);

		return i;
	}

	Game::script_s* Menus::LoadMenuScript(const std::string& name, const std::string& buffer)
	{
		auto* script = static_cast<Game::script_s*>(Game::GetClearedMemory(sizeof(Game::script_s) + 1 + buffer.length()));
		if (!script) return nullptr;

		strcpy_s(script->filename, sizeof(script->filename), name.data());
		script->buffer = reinterpret_cast<char*>(script + 1);

		*(script->buffer + buffer.length()) = '\0';

		script->script_p = script->buffer;
		script->lastscript_p = script->buffer;
		script->length = static_cast<int>(buffer.length());
		script->end_p = &script->buffer[buffer.length()];
		script->line = 1;
		script->lastline = 1;
		script->tokenavailable = 0;

		Game::PS_CreatePunctuationTable(script, Game::default_punctuations);
		script->punctuations = Game::default_punctuations;

		std::memcpy(script->buffer, buffer.data(), script->length + 1);

		script->length = Game::Com_Compress(script->buffer);

		return script;
	}

	int Menus::LoadMenuSource(const std::string& name, const std::string& buffer)
	{
		const auto handle = ReserveSourceHandle();
		if (!IsValidSourceHandle(handle)) return 0; // No free source slot!

		auto* script = LoadMenuScript(name, buffer);
		if (!script)
		{
			Game::sourceFiles[handle] = nullptr; // Free reserved slot
			return 0;
		}

		auto* source = static_cast<Game::source_s*>(Game::GetMemory(sizeof(Game::source_s)));
		std::memset(source, 0, sizeof(Game::source_s));

		script->next = nullptr;

		strncpy_s(source->filename, name.data(), _TRUNCATE);
		source->scriptstack = script;
		source->tokens = nullptr;
		source->defines = nullptr;
		source->indentstack = nullptr;
		source->skip = 0;
		source->definehash = static_cast<Game::define_s**>(Game::GetClearedMemory(DEFINEHASHSIZE * sizeof(Game::define_s*)));

		Game::sourceFiles[handle] = source;

		return handle;
	}

	bool Menus::IsValidSourceHandle(int handle)
	{
		return (handle > 0 && handle < MAX_SOURCEFILES && Game::sourceFiles[handle]);
	}

	Game::menuDef_t* Menus::ParseMenu(int handle)
	{
		Utils::Memory::Allocator* allocator = Utils::Memory::GetAllocator();
		auto* menu = allocator->allocate<Game::menuDef_t>();
		if (!menu) return nullptr;

		menu->items = allocator->allocateArray<Game::itemDef_s*>(512);
		if (!menu->items)
		{
			allocator->free(menu);
			return nullptr;
		}

		Game::pc_token_s token;
		if (!Game::PC_ReadTokenHandle(handle, &token) || token.string[0] != '{')
		{
			allocator->free(menu->items);
			allocator->free(menu);
			return nullptr;
		}

		while (true)
		{
			ZeroMemory(&token, sizeof(token));

			if (!Game::PC_ReadTokenHandle(handle, &token))
			{
				Game::PC_SourceError(handle, "end of file inside menu\n");
				break; // Fail
			}

			if (*token.string == '}')
			{
				break; // Success
			}

			auto* key = KeywordHashFind(menuParseKeywordHash, token.string);
			if (!key)
			{
				Game::PC_SourceError(handle, "unknown menu keyword %s", token.string);
				continue;
			}

			if (!key->func(menu, handle))
			{
				Game::PC_SourceError(handle, "couldn't parse menu keyword %s", token.string);
				break; // Fail
			}
		}

		if (!menu->window.name)
		{
			Game::PC_SourceError(handle, "menu has no name");
			allocator->free(menu->items);
			allocator->free(menu);
			return nullptr;
		}

		OverrideMenu(menu);
		RemoveMenu(menu->window.name);
		MenuList[menu->window.name] = menu;

		return menu;
	}

	std::vector<std::pair<bool, Game::menuDef_t*>> Menus::LoadScriptMenuFromFile(const std::string& file)
	{
		std::vector<std::pair<bool, Game::menuDef_t*>> menus{};
		FileSystem::File menuFile(file);

		if (menuFile.exists())
		{
			Game::pc_token_s token;
			const auto handle = LoadMenuSource(file, menuFile.getBuffer());

			if (IsValidSourceHandle(handle))
			{
				while (true)
				{
					ZeroMemory(&token, sizeof(token));

					if (!Game::PC_ReadTokenHandle(handle, &token) || token.string[0] == '}')
					{
						break;
					}

					if (!_stricmp(token.string, "loadmenu"))
					{
						Game::PC_ReadTokenHandle(handle, &token);

						const auto menuPath = Utils::String::VA("ui_mp\\%s.menu", token.string);
						std::vector<std::pair<bool, Game::menuDef_t*>> subMenu = LoadScriptMenuFromFile(menuPath);
						Utils::Merge(&menus, subMenu);
					}

					if (!_stricmp(token.string, "menudef"))
					{
						auto* menudef = ParseMenu(handle);
						if (menudef)
						{
							menus.emplace_back(std::make_pair(true, menudef)); // Custom menu
						}
					}
				}

				FreeMenuSource(handle);
			}
		}

		return menus;
	}

	Game::menuDef_t* Menus::GetMenu(const std::string& name)
	{
		if (Menus::MenuList.contains(name))
		{
			return Menus::MenuList.at(name);
		}

		return nullptr;
	}

	std::vector<std::pair<bool, Game::menuDef_t*>> Menus::LoadOverrideForNativeMenu(Game::menuDef_t* menudef)
	{
		assert(menudef->window.name);

		std::vector<std::pair<bool, Game::menuDef_t*>> menus = LoadScriptMenuFromFile(Utils::String::VA("ui_mp\\%s.menu", menudef->window.name));

		if (menus.empty())
		{
			menus.emplace_back(std::make_pair(false, menudef)); // Native menu
		}

		return menus;
	}

	Game::MenuList* Menus::LoadScriptMenu(const char* menu)
	{
		Utils::Memory::Allocator* allocator = Utils::Memory::GetAllocator();

		auto menus = LoadScriptMenuFromFile(menu);
		if (menus.empty()) return nullptr;

		// Allocate new menu list
		auto* newList = allocator->allocate<Game::MenuList>();
		if (!newList) return nullptr;

		newList->menus = allocator->allocateArray<Game::menuDef_t*>(menus.size());
		if (!newList->menus)
		{
			allocator->free(newList);
			return nullptr;
		}

		newList->name = allocator->duplicateString(menu);
		newList->menuCount = static_cast<int>(menus.size());

		// Copy new menus
		for (unsigned int i = 0; i < menus.size(); ++i)
		{
			newList->menus[i] = menus[i].second;
		}

		RemoveMenuList(newList->name);
		MenuListList[newList->name] = newList;

		return newList;
	}

	void Menus::SafeMergeMenus(std::vector<std::pair<bool, Game::menuDef_t*>>* menus, std::vector<std::pair<bool, Game::menuDef_t*>> newMenus)
	{
		// Check if we overwrote a menu
		for (auto i = menus->begin(); i != menus->end();)
		{
			// Try to find the native menu
			bool found = !i->first; // Only if custom menu, try to find it

			// If there is none, try to find a custom menu
			if (!found)
			{
				for (auto& entry : Menus::MenuList)
				{
					if (i->second == entry.second)
					{
						found = true;
						break;
					}
				}
			}

			// Remove the menu if it has been deallocated (not found)
			if (!found)
			{
				i = menus->erase(i);
				continue;
			}

			bool increment = true;

			// Remove the menu if it has been loaded twice
			for (auto& newMenu : newMenus)
			{
				if (i->second->window.name == std::string(newMenu.second->window.name))
				{
					RemoveMenu(i->second);

					i = menus->erase(i);
					increment = false;
					break;
				}
			}

			if (increment) ++i;
		}

		Utils::Merge(menus, newMenus);
	}

	Game::MenuList* Menus::LoadMenuList(Game::MenuList* menuList)
	{
		Utils::Memory::Allocator* allocator = Utils::Memory::GetAllocator();

		std::vector<std::pair<bool, Game::menuDef_t*>> menus;

		for (int i = 0; i < menuList->menuCount; ++i)
		{
			if (!menuList->menus[i]) continue;
			SafeMergeMenus(&menus, LoadOverrideForNativeMenu(menuList->menus[i]));
		}

		// Allocate new menu list
		auto* newList = allocator->allocate<Game::MenuList>();
		if (!newList) return menuList;

		auto size = menus.size();
		newList->menus = allocator->allocateArray<Game::menuDef_t*>(size);
		if (!newList->menus)
		{
			allocator->free(newList);
			return menuList;
		}

		newList->name = allocator->duplicateString(menuList->name);
		newList->menuCount = static_cast<int>(size);

		// Copy new menus
		for (unsigned int i = 0; i < menus.size(); ++i)
		{
			newList->menus[i] = menus[i].second;
		}

		RemoveMenuList(newList->name);
		MenuListList[newList->name] = newList;

		return newList;
	}

	void Menus::FreeScript(Game::script_s* script)
	{
		if (script->punctuationtable)
		{
			Game::FreeMemory(script->punctuationtable);
		}

		Game::FreeMemory(script);
	}

	void Menus::FreeMenuSource(int handle)
	{
		if (!IsValidSourceHandle(handle)) return;

		auto* source = Game::sourceFiles[handle];

		while (source->scriptstack)
		{
			auto* script = source->scriptstack;
			source->scriptstack = source->scriptstack->next;
			FreeScript(script);
		}

		while (source->tokens)
		{
			auto* token = source->tokens;
			source->tokens = source->tokens->next;

			Game::FreeMemory(token);
			--*Game::numtokens;
		}

		for (auto i = 0; i < DEFINEHASHSIZE; ++i)
		{
			while (source->definehash[i])
			{
				auto* define = source->definehash[i];
				source->definehash[i] = source->definehash[i]->hashnext;
				Game::PC_FreeDefine(define);
			}
		}

		while (source->indentstack)
		{
			auto* indent = source->indentstack;
			source->indentstack = source->indentstack->next;
			Game::FreeMemory(indent);
		}

		if (source->definehash)
		{
			Game::FreeMemory(source->definehash);
		}

		Game::FreeMemory(source);

		Game::sourceFiles[handle] = nullptr;
	}

	void Menus::Menu_FreeItemMemory(Game::itemDef_s* item)
	{
		AssertOffset(Game::itemDef_s, floatExpressionCount, 0x13C);

		for (auto i = 0; i < item->floatExpressionCount; ++i)
		{
			Game::free_expression(item->floatExpressions[i].expression);
		}

		item->floatExpressionCount = 0;
	}

	void Menus::FreeMenu(Game::menuDef_t* menu)
	{
		Utils::Memory::Allocator* allocator = Utils::Memory::GetAllocator();

		if (menu->items)
		{
			for (int i = 0; i < menu->itemCount; ++i)
			{
#if 1
				Menu_FreeItemMemory(menu->items[i]);
#endif
			}

			allocator->free(menu->items);
		}
#if 1
		Game::free_expression(menu->visibleExp);
		Game::free_expression(menu->rectXExp);
		Game::free_expression(menu->rectYExp);
		Game::free_expression(menu->rectWExp);
		Game::free_expression(menu->rectHExp);
		Game::free_expression(menu->openSoundExp);
		Game::free_expression(menu->closeSoundExp);
#endif

		allocator->free(menu);
	}

	void Menus::FreeMenuList(Game::MenuList* menuList)
	{
		if (!menuList) return;
		Utils::Memory::Allocator* allocator = Utils::Memory::GetAllocator();

		// Keep our compiler happy
		Game::MenuList list = { menuList->name, menuList->menuCount, menuList->menus };

		allocator->free(list.name);
		allocator->free(list.menus);
		allocator->free(menuList);
	}

	void Menus::RemoveMenu(const std::string& menu)
	{
		auto i = MenuList.find(menu);
		if (i != MenuList.end())
		{
			if (i->second) FreeMenu(i->second);
			i = MenuList.erase(i);
		}
	}

	void Menus::RemoveMenu(Game::menuDef_t* menudef)
	{
		for (auto i = MenuList.begin(); i != MenuList.end();)
		{
			if (i->second == menudef)
			{
				FreeMenu(menudef);
				i = MenuList.erase(i);
			}
			else
			{
				++i;
			}
		}
	}

	void Menus::RemoveMenuList(const std::string& menuList)
	{
		auto i = MenuListList.find(menuList);
		if (i != MenuListList.end())
		{
			if (i->second)
			{
				for (auto j = 0; j < i->second->menuCount; ++j)
				{
					RemoveMenu(i->second->menus[j]);
				}

				FreeMenuList(i->second);
			}

			i = MenuListList.erase(i);
		}
	}

	// This is actually a really important function
	// It checks if we have already loaded the menu we passed and replaces its instances in memory
	// Due to deallocating the old menu, the game might crash on not being able to handle its old instance
	// So we need to override it in our menu lists and the game's ui context
	// EDIT: We might also remove the old instances inside RemoveMenu
	// EDIT2: Removing old instances without having a menu to replace them with might leave a nullptr
	// EDIT3: Wouldn't it be better to check if the new menu we're trying to load has already been loaded and not was not deallocated and return that one instead of loading a new one?
	void Menus::OverrideMenu(Game::menuDef_t* menu)
	{
		if (!menu || !menu->window.name) return;
		std::string name = menu->window.name;

		// Find the old menu
		if (auto i = MenuList.find(name); i != MenuList.end())
		{
			// We have found it, *yay*
			Game::menuDef_t* oldMenu = i->second;

			// Replace every old instance with our new one in the ui context
			for (int j = 0; j < Game::uiContext->menuCount; ++j)
			{
				if (Game::uiContext->Menus[j] == oldMenu)
				{
					Game::uiContext->Menus[j] = menu;
				}
			}

			// Replace every old instance with our new one in our menu lists
			for (auto j = MenuListList.begin(); j != MenuListList.end(); ++j)
			{
				Game::MenuList* list = j->second;

				if (list && list->menus)
				{
					for (int k = 0; k < list->menuCount; ++k)
					{
						if (list->menus[k] == oldMenu)
						{
							list->menus[k] = menu;
						}
					}
				}
			}
		}
	}

	void Menus::RemoveMenuList(Game::MenuList* menuList)
	{
		if (!menuList || !menuList->name) return;
		RemoveMenuList(menuList->name);
	}

	Game::XAssetHeader Menus::MenuFindHook(Game::XAssetType /*type*/, const std::string& filename)
	{
		return { Game::Menus_FindByName(Game::uiContext, filename.data()) };
	}

	Game::XAssetHeader Menus::MenuListFindHook(Game::XAssetType type, const std::string& filename)
	{
		Game::XAssetHeader header = { nullptr };

		// Free the last menulist and ui context, as we have to rebuild it with the new menus
		if (MenuListList.find(filename) != MenuListList.end())
		{
			Game::MenuList* list = MenuListList[filename];

			for (int i = 0; list && list->menus && i < list->menuCount; ++i)
			{
				RemoveMenuFromContext(Game::uiContext, list->menus[i]);
			}

			RemoveMenuList(filename);
		}

		if (Utils::String::EndsWith(filename, ".menu"))
		{
			if (FileSystem::File(filename).exists())
			{
				header.menuList = LoadScriptMenu(filename.data());
				if (header.menuList) return header;
			}
		}

		Game::MenuList* menuList = Game::DB_FindXAssetHeader(type, filename.data()).menuList;
		header.menuList = menuList;

		if (menuList && reinterpret_cast<DWORD>(menuList) != 0xDDDDDDDD)
		{
			// Parse scriptmenus!
			if ((menuList->menuCount > 0 && menuList->menus[0] && menuList->menus[0]->window.name == "default_menu"s))
			{
				if (FileSystem::File(filename).exists())
				{
					header.menuList = LoadScriptMenu(filename.data());

					// Reset, if we didn't find scriptmenus
					if (!header.menuList)
					{
						header.menuList = menuList;
					}
				}
			}
			else
			{
				header.menuList = LoadMenuList(menuList);
			}
		}
		else
		{
			header.menuList = nullptr;
		}

		return header;
	}

	bool Menus::IsMenuVisible(Game::UiContext* dc, Game::menuDef_t* menu)
	{
		if (menu && menu->window.name)
		{
			if (menu->window.name == "connect"s) // Check if we're supposed to draw the loadscreen
			{
				const auto* originalConnect = AssetHandler::FindOriginalAsset(Game::XAssetType::ASSET_TYPE_MENU, "connect").menu;

				if (originalConnect == menu) // Check if we draw the original loadscreen
				{
					if (MenuList.contains("connect")) // Check if we have a custom load screen, to prevent drawing the original one on top
					{
						return false;
					}
				}
			}
		}

		return Game::Menu_IsVisible(dc, menu);
	}

	void Menus::RemoveMenuFromContext(Game::UiContext* dc, Game::menuDef_t* menu)
	{
		// Search menu in context
		int i = 0;
		for (; i < dc->menuCount; ++i)
		{
			if (dc->Menus[i] == menu)
			{
				break;
			}
		}

		// Remove from stack
		if (i < dc->menuCount)
		{
			for (; i < dc->menuCount - 1; ++i)
			{
				dc->Menus[i] = dc->Menus[i + 1];
			}

			// Clear last menu
			dc->Menus[--dc->menuCount] = nullptr;
		}
	}

	void Menus::Add(const std::string& menu)
	{
		CustomMenus.push_back(menu);
	}

	Menus::Menus()
	{
		// Free all on UI_Shutdown
		menuParseKeywordHash = reinterpret_cast<Game::KeywordHashEntry<Game::menuDef_t, 128, 3523>**>(0x63AE928);

		if (ZoneBuilder::IsEnabled())
		{
			Game::Menu_Setup(Game::uiContext);
		}

		if (Dedicated::IsEnabled()) return;

		// Intercept asset finding
		AssetHandler::OnFind(Game::ASSET_TYPE_MENU, MenuFindHook);
		AssetHandler::OnFind(Game::ASSET_TYPE_MENULIST, MenuListFindHook);

		// Don't open connect menu
		// Utils::Hook::Nop(0x428E48, 5);

		// Use the connect menu open call to update server motds
		Utils::Hook(0x428E48, []
			{
				if (!Party::GetMotd().empty() && Party::Target() == *Game::connectedHost)
				{
					Dvar::Var("didyouknow").set(Party::GetMotd());
				}
			}, HOOK_CALL).install()->quick();

			// Intercept menu painting
			Utils::Hook(0x4FFBDF, IsMenuVisible, HOOK_CALL).install()->quick();

			// disable the 2 new tokens in ItemParse_rect (Fix by NTA. Probably because he didn't want to update the menus)
			Utils::Hook::Set<std::uint8_t>(0x640693, 0xEB);

			// don't load ASSET_TYPE_MENU assets for every menu (might cause patch menus to fail)
			//Utils::Hook::Nop(0x453406, 5);

			// make Com_Error and similar go back to main_text instead of menu_xboxlive.
			Utils::Hook::SetString(0x6FC790, "main_text");

			Command::Add("openmenu", [](const Command::Params* params)
				{
					if (params->size() != 2)
					{
						Logger::Print("USAGE: openmenu <menu name>\n");
						return;
					}

					// Not quite sure if we want to do this if we're not ingame, but it's only needed for ingame menus.
					if ((*Game::cl_ingame)->current.enabled)
					{
						Game::Key_SetCatcher(0, Game::KEYCATCH_UI);
					}

					Game::Menus_OpenByName(Game::uiContext, params->get(1));
				});

			// Define custom menus here
			Add("ui_mp/changelog.menu");
			Add("ui_mp/iw4x_credits.menu");
			Add("ui_mp/menu_first_launch.menu");
			Add("ui_mp/mod_download_popmenu.menu");
			Add("ui_mp/pc_options_game.menu");
			Add("ui_mp/pc_options_gamepad.menu");
			Add("ui_mp/pc_options_multi.menu");
			Add("ui_mp/popup_customclan.menu");
			Add("ui_mp/popup_customtitle.menu");
			Add("ui_mp/popup_friends.menu");
			Add("ui_mp/resetclass.menu");
			Add("ui_mp/security_increase_popmenu.menu");
			Add("ui_mp/startup_messages.menu");
			Add("ui_mp/stats_reset.menu");
			Add("ui_mp/stats_unlock.menu");
			Add("ui_mp/theater_menu.menu");
	}
}
