#pragma once

namespace Assets
{
	class ImenuDef_t : public Components::AssetHandler::IAsset
	{
	public:
		Game::XAssetType getType() override { return Game::XAssetType::ASSET_TYPE_MENU; }

		void save(Game::XAssetHeader header, Components::ZoneBuilder::Zone* builder) override;
		void mark(Game::XAssetHeader header, Components::ZoneBuilder::Zone* builder) override;
		void load(Game::XAssetHeader* header, const std::string& name, Components::ZoneBuilder::Zone* builder) override;

		static std::unordered_map<std::string, Game::menuDef_t*> LoadedMenus;

	private:
		template <typename T> void save_windowDef_t(Game::windowDef_t* asset, T* dest, Components::ZoneBuilder::Zone* builder)
		{
			Utils::Stream* buffer = builder->getBuffer();

			if (asset->name)
			{
				buffer->saveString(asset->name);
				Utils::Stream::ClearPointer(&dest->window.name);
			}

			if (asset->group)
			{
				buffer->saveString(asset->group);
				Utils::Stream::ClearPointer(&dest->window.group);
			}

			if (asset->background)
			{
				dest->window.background = builder->saveSubAsset(Game::XAssetType::ASSET_TYPE_MATERIAL, asset->background).material;
			}
		}
		void save_ExpressionSupportingData(Game::ExpressionSupportingData* asset, Components::ZoneBuilder::Zone* builder);
		void save_Statement_s(Game::Statement_s* asset, Components::ZoneBuilder::Zone* builder);
		void save_StatementIfNeeded(Utils::Stream* buffer, Game::Statement_s* asset, Game::Statement_s** destination, Components::ZoneBuilder::Zone* builder);
		void save_MenuEventHandlerSet(Game::MenuEventHandlerSet* asset, Components::ZoneBuilder::Zone* builder);
		void save_ItemKeyHandler(Game::ItemKeyHandler* asset, Components::ZoneBuilder::Zone* builder);
		void save_itemDefData_t(Game::itemDefData_t* asset, int type, Game::itemDef_s* dest, Components::ZoneBuilder::Zone* builder);
		void save_itemDef_s(Game::itemDef_s *asset, Components::ZoneBuilder::Zone* builder);
	};
}
