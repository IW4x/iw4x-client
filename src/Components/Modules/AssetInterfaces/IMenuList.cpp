#include <STDInclude.hpp>
#include "IMenuList.hpp"

namespace Assets
{
	void IMenuList::load(Game::XAssetHeader* header, const std::string& scriptMenuFileName, Components::ZoneBuilder::Zone* builder)
	{
		Utils::Memory::Allocator* allocator = builder->getAllocator();
		auto* newList = allocator->allocate<Game::MenuList>();
		if (newList)
		{
			newList->name = allocator->duplicateString(scriptMenuFileName);
			auto menus = Components::Menus::LoadScriptMenuFromFile(scriptMenuFileName);

			if (menus.empty())
			{
				return;
			}

			// Allocate new menu list
			newList->menus = allocator->allocateArray<Game::menuDef_t*>(menus.size());
			if (!newList->menus)
			{
				Components::Logger::Error(Game::ERR_FATAL, "No more memory to allocate menu list");
				return;
			}

			newList->name = allocator->duplicateString(scriptMenuFileName);
			newList->menuCount = menus.size();

			// Copy new menus
			for (unsigned int i = 0; i < menus.size(); ++i)
			{
				newList->menus[i] = menus[i].second;
			}

			header->menuList = newList;
		}
	}
	void IMenuList::mark(Game::XAssetHeader header, Components::ZoneBuilder::Zone* builder)
	{
		// We have nothing to do since we loaded the whole menu list earlier in Load()		auto* asset = header.menuList;

		for (int i = 0; i < header.menuList->menuCount; ++i)
		{
			if (header.menuList->menus[i])
			{
				builder->loadAsset(Game::XAssetType::ASSET_TYPE_MENU, header.menuList->menus[i]);
			}
		}
	}

	void IMenuList::save(Game::XAssetHeader header, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::MenuList, 12);

		Utils::Stream* buffer = builder->getBuffer();
		Game::MenuList* asset = header.menuList;
		auto* dest = buffer->dest<Game::MenuList>();

		buffer->save(asset);

		buffer->pushBlock(Game::XFILE_BLOCK_VIRTUAL);

		if (asset->name)
		{
			buffer->saveString(builder->getAssetName(this->getType(), asset->name));
			Utils::Stream::ClearPointer(&dest->name);
		}

		if (asset->menus)
		{
			buffer->align(Utils::Stream::ALIGN_4);

			auto** destMenus = buffer->dest<Game::menuDef_t*>();
			buffer->saveArray(asset->menus, asset->menuCount);

			for (int i = 0; i < asset->menuCount; ++i)
			{
				destMenus[i] = builder->saveSubAsset(Game::XAssetType::ASSET_TYPE_MENU, asset->menus[i]).menu;
			}
		}

		buffer->popBlock();
	}
}
