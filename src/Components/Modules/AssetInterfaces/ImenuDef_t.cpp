#include <STDInclude.hpp>
#include "ImenuDef_t.hpp"

namespace Assets
{

	std::unordered_map<std::string, Game::menuDef_t*> ImenuDef_t::LoadedMenus;

	void ImenuDef_t::load(Game::XAssetHeader* header, const std::string& name, Components::ZoneBuilder::Zone* /* builder */)
	{
		// Loading menus from disk is not supported!
		// Use menu lists instead! (A scriptmenu might contain MORE THAN ONE MENU, which is tricky!)
		header->menu = Components::AssetHandler::FindOriginalAsset(this->getType(), name.data()).menu;

		if (header->menu == nullptr)
		{
			header->menu = Components::Menus::GetMenu(name);
		}

		if (header->menu == nullptr)
		{
			printf("");
		}
	}


	void ImenuDef_t::mark(Game::XAssetHeader header, Components::ZoneBuilder::Zone* builder)
	{
		auto* asset = header.menu;

		if (asset->window.background)
		{
			builder->loadAsset(Game::XAssetType::ASSET_TYPE_MATERIAL, asset->window.background);
		}

		// mark items
		for (int i = 0; i < asset->itemCount; ++i)
		{
			if (asset->items[i]->window.background)
			{
				builder->loadAsset(Game::XAssetType::ASSET_TYPE_MATERIAL, asset->items[i]->window.background);
			}

			if (asset->items[i]->focusSound)
			{
				builder->loadAsset(Game::XAssetType::ASSET_TYPE_SOUND, asset->items[i]->focusSound);
			}

			if (asset->items[i]->type == 6 && asset->items[i]->typeData.listBox &&
				asset->items[i]->typeData.listBox->selectIcon)
			{
				builder->loadAsset(Game::XAssetType::ASSET_TYPE_MATERIAL, asset->items[i]->typeData.listBox->selectIcon);
			}
		}
	}

	void ImenuDef_t::save_ExpressionSupportingData(Game::ExpressionSupportingData* asset, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::ExpressionSupportingData, 24);
		Utils::Stream* buffer = builder->getBuffer();

#ifdef WRITE_LOGS
		buffer->enterStruct("ExpressionSupportingData");
#endif

		buffer->align(Utils::Stream::ALIGN_4);

		auto* dest = buffer->dest<Game::ExpressionSupportingData>();
		buffer->save(asset);

		if (asset->uifunctions.functions)
		{
			buffer->align(Utils::Stream::ALIGN_4);

			auto** destStatement = buffer->dest<Game::Statement_s*>();
			buffer->saveArray(asset->uifunctions.functions, asset->uifunctions.totalFunctions);

			for (int i = 0; i < asset->uifunctions.totalFunctions; ++i)
			{
				if (asset->uifunctions.functions[i])
				{
					this->save_StatementIfNeeded(buffer, asset->uifunctions.functions[i], &destStatement[i], builder);
				}
			}

			Utils::Stream::ClearPointer(&dest->uifunctions.functions);
		}

		if (asset->staticDvarList.staticDvars)
		{
			buffer->align(Utils::Stream::ALIGN_4);

			auto** destStaticDvars = buffer->dest<Game::StaticDvar*>();
			buffer->saveArray(asset->staticDvarList.staticDvars, asset->staticDvarList.numStaticDvars);

			for (auto i = 0; i < asset->staticDvarList.numStaticDvars; ++i)
			{
				if (asset->staticDvarList.staticDvars[i])
				{
					Utils::Stream::ClearPointer(&destStaticDvars[i]);

					buffer->align(Utils::Stream::ALIGN_4);
					auto* destStaticDvar = buffer->dest<Game::StaticDvar>();
					buffer->save(asset->staticDvarList.staticDvars[i]);

					if (asset->staticDvarList.staticDvars[i]->dvarName)
					{
						buffer->saveString(asset->staticDvarList.staticDvars[i]->dvarName);
						Utils::Stream::ClearPointer(&destStaticDvar->dvarName);
					}
				}
			}

			Utils::Stream::ClearPointer(&dest->staticDvarList.staticDvars);
		}

		if (asset->uiStrings.strings)
		{
			buffer->align(Utils::Stream::ALIGN_4);

			const auto** destUIStrings = buffer->dest<const char*>();
			buffer->saveArray(asset->uiStrings.strings, asset->uiStrings.totalStrings);

			for (int i = 0; i < asset->uiStrings.totalStrings; ++i)
			{
				if (asset->uiStrings.strings[i])
				{
					buffer->saveString(asset->uiStrings.strings[i]);
					Utils::Stream::ClearPointer(&destUIStrings[i]);
				}
			}
		}
#ifdef WRITE_LOGS
		buffer->leaveStruct();
#endif
	}

	void ImenuDef_t::save_Statement_s(Game::Statement_s* asset, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::Statement_s, 24);
		AssertSize(Game::expressionEntry, 12);
		Utils::Stream* buffer = builder->getBuffer();

#ifdef WRITE_LOGS
		buffer->enterStruct("Statement_s");
#endif

		// Write header data
		auto* dest = buffer->dest<Game::Statement_s>();
		buffer->save(asset);

		// Write statement entries
		if (asset->entries)
		{
#ifdef WRITE_LOGS
			buffer->enterStruct("statement entries");
#endif
			buffer->align(Utils::Stream::ALIGN_4);

			// Write entries
			auto* destEntries = buffer->dest<Game::expressionEntry>();
			buffer->save(asset->entries, sizeof(Game::expressionEntry), asset->numEntries);

			// Loop through entries
			for (int i = 0; i < asset->numEntries; ++i)
			{
#ifdef WRITE_LOGS
				buffer->enterStruct("entry");
#endif
				if (asset->entries[i].type)
				{
					switch (asset->entries[i].data.operand.dataType)
					{
						// Those types do not require additional data
					case 0:
					case 1:
						break;

						// Expression string
					case 2:
						if (asset->entries[i].data.operand.internals.stringVal.string)
						{
							buffer->saveString(asset->entries[i].data.operand.internals.stringVal.string);
							Utils::Stream::ClearPointer(&destEntries[i].data.operand.internals.stringVal.string);
						}
						break;

						// Function
					case 3:
						if (asset->entries[i].data.operand.internals.function)
						{
							buffer->align(Utils::Stream::ALIGN_4);
							this->save_Statement_s(asset->entries[i].data.operand.internals.function, builder);
							Utils::Stream::ClearPointer(&destEntries[i].data.operand.internals.function);
						}
						break;
					}
				}
#ifdef WRITE_LOGS
				buffer->leaveStruct();
#endif
			}
#ifdef WRITE_LOGS
			buffer->leaveStruct();
#endif
		}

		if (asset->supportingData)
		{
			//if (builder->hasPointer(asset->supportingData))
			//{
			//	dest->supportingData = builder->getPointer(asset->supportingData);
			//}
			//else
			{
				this->save_ExpressionSupportingData(asset->supportingData, builder);
				Utils::Stream::ClearPointer(&dest->supportingData);
			}
		}
#ifdef WRITE_LOGS
		buffer->leaveStruct();
#endif
	}

	void ImenuDef_t::save_StatementIfNeeded(Utils::Stream* buffer, Game::Statement_s* asset, Game::Statement_s** destination, Components::ZoneBuilder::Zone* builder)
	{
		if (builder->hasPointer(asset))
		{
			*destination = builder->getPointer(asset);
		}
		else
		{
			buffer->align(Utils::Stream::ALIGN_4);
			builder->storePointer(asset);

			this->save_Statement_s(asset, builder);
			Utils::Stream::ClearPointer(destination);
		}
	}

	void ImenuDef_t::save_MenuEventHandlerSet(Game::MenuEventHandlerSet* asset, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::MenuEventHandlerSet, 8);
		Utils::Stream* buffer = builder->getBuffer();

#ifdef WRITE_LOGS
		buffer->enterStruct("MenuEventHandlerSet");
#endif

		// Write header data
		auto* destset = buffer->dest<Game::MenuEventHandlerSet>();
		buffer->save(asset);

		// Event handlers
		if (asset->eventHandlers)
		{
			buffer->align(Utils::Stream::ALIGN_4);

			// Write pointers to zone
			buffer->save(asset->eventHandlers, sizeof(Game::MenuEventHandler*), asset->eventHandlerCount);

			// Loop through eventHandlers
			for (auto i = 0; i < asset->eventHandlerCount; ++i)
			{
				if (asset->eventHandlers[i])
				{
					buffer->align(Utils::Stream::ALIGN_4);
#ifdef WRITE_LOGS
					buffer->enterStruct("MenuEventHandler");
#endif

					// Write menu event handler
					auto* dest = buffer->dest<Game::MenuEventHandler>();
					buffer->save(asset->eventHandlers[i]);

					// Write additional data based on type
					switch (asset->eventHandlers[i]->eventType)
					{
						// unconditional scripts
					case 0:
						if (asset->eventHandlers[i]->eventData.unconditionalScript)
						{
							buffer->saveString(asset->eventHandlers[i]->eventData.unconditionalScript);
							Utils::Stream::ClearPointer(&dest->eventData.unconditionalScript);
						}
						break;

						// ConditionalScript
					case 1:
						if (asset->eventHandlers[i]->eventData.conditionalScript)
						{
							buffer->align(Utils::Stream::ALIGN_4);
							auto* destConditionalScript = buffer->dest<Game::ConditionalScript>();
							buffer->save(asset->eventHandlers[i]->eventData.conditionalScript);

							// eventExpression
							if (asset->eventHandlers[i]->eventData.conditionalScript->eventExpression)
							{
								buffer->align(Utils::Stream::ALIGN_4);
								this->save_Statement_s(asset->eventHandlers[i]->eventData.conditionalScript->eventExpression, builder);
								Utils::Stream::ClearPointer(&destConditionalScript->eventExpression);
							}

							// eventHandlerSet
							if (asset->eventHandlers[i]->eventData.conditionalScript->eventHandlerSet)
							{
								buffer->align(Utils::Stream::ALIGN_4);
								this->save_MenuEventHandlerSet(asset->eventHandlers[i]->eventData.conditionalScript->eventHandlerSet, builder);
								Utils::Stream::ClearPointer(&destConditionalScript->eventHandlerSet);
							}

							Utils::Stream::ClearPointer(&dest->eventData.conditionalScript);
						}
						break;

						// elseScript
					case 2:
						if (asset->eventHandlers[i]->eventData.elseScript)
						{
							buffer->align(Utils::Stream::ALIGN_4);
							this->save_MenuEventHandlerSet(asset->eventHandlers[i]->eventData.elseScript, builder);
							Utils::Stream::ClearPointer(&dest->eventData.elseScript);
						}
						break;

						// localVarData expressions
					case 3:
					case 4:
					case 5:
					case 6:
						if (asset->eventHandlers[i]->eventData.setLocalVarData)
						{
							buffer->align(Utils::Stream::ALIGN_4);

							// header data
							auto* destLocalVarData = buffer->dest<Game::SetLocalVarData>();
							buffer->save(asset->eventHandlers[i]->eventData.setLocalVarData);

							// localVarName
							if (asset->eventHandlers[i]->eventData.setLocalVarData->localVarName)
							{
								buffer->saveString(asset->eventHandlers[i]->eventData.setLocalVarData->localVarName);
								Utils::Stream::ClearPointer(&destLocalVarData->localVarName);
							}

							// statement
							if (asset->eventHandlers[i]->eventData.setLocalVarData->expression)
							{
								buffer->align(Utils::Stream::ALIGN_4);
								this->save_Statement_s(asset->eventHandlers[i]->eventData.setLocalVarData->expression, builder);
								Utils::Stream::ClearPointer(&destLocalVarData->expression);
							}

							Utils::Stream::ClearPointer(&dest->eventData.setLocalVarData);
						}
						break;
					}
#ifdef WRITE_LOGS
					buffer->leaveStruct();
#endif
				}
			}

			Utils::Stream::ClearPointer(&destset->eventHandlers);
		}
#ifdef WRITE_LOGS
		buffer->leaveStruct();
#endif
	}

	void ImenuDef_t::save_ItemKeyHandler(Game::ItemKeyHandler* asset, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::ItemKeyHandler, 12);
		Utils::Stream* buffer = builder->getBuffer();

#ifdef WRITE_LOGS
		buffer->enterStruct("ItemKeyHandler");
#endif

		while (asset)
		{
			// Write header
			auto* dest = buffer->dest<Game::ItemKeyHandler>();
			buffer->save(asset);

			// MenuEventHandlerSet
			if (asset->action)
			{
				buffer->align(Utils::Stream::ALIGN_4);
				this->save_MenuEventHandlerSet(asset->action, builder);
				Utils::Stream::ClearPointer(&dest->action);
			}

			if (asset->next)
			{
				// align every index, besides the first one?
				buffer->align(Utils::Stream::ALIGN_4);
			}

			// Next key handler
			asset = asset->next;
		}
#ifdef WRITE_LOGS
		buffer->leaveStruct();
#endif
	}

#define EVENTHANDLERSET(__index) \
		if (asset->__index) \
		{ \
			buffer->align(Utils::Stream::ALIGN_4); \
			this->save_MenuEventHandlerSet(asset->__index, builder); \
			Utils::Stream::ClearPointer(&dest->__index); \
		}

#define STATEMENT(__index) \
		if (asset->__index) \
		{ \
			buffer->align(Utils::Stream::ALIGN_4); \
			this->save_Statement_s(asset->__index, builder); \
			Utils::Stream::ClearPointer(&dest->__index); \
		}

	void ImenuDef_t::save_itemDefData_t(Game::itemDefData_t* asset, int type, Game::itemDef_s* dest, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::newsTickerDef_s, 28);
		AssertSize(Game::listBoxDef_s, 324);
		AssertSize(Game::editFieldDef_s, 32);
		AssertSize(Game::multiDef_s, 392);

		Utils::Stream* buffer = builder->getBuffer();

#ifdef WRITE_LOGS
		buffer->enterStruct("itemDefData_t");
#endif

		// feeder
		if (type == 6)
		{
			buffer->align(Utils::Stream::ALIGN_4);
			auto* destlb = buffer->dest<Game::listBoxDef_s>();
			buffer->save(asset->listBox);

			if (asset->listBox->onDoubleClick)
			{
				buffer->align(Utils::Stream::ALIGN_4);
				this->save_MenuEventHandlerSet(asset->listBox->onDoubleClick, builder);
			}

			if (asset->listBox->selectIcon)
			{
				destlb->selectIcon = builder->saveSubAsset(Game::XAssetType::ASSET_TYPE_MATERIAL, asset->listBox->selectIcon).material;
			}
		}
		// HexRays spaghetti
		else if (type != 4 && type != 9 && type != 16 && type != 18 && type != 11 && type != 14 && type != 10 && type != 17	&& type != 22 && type != 23 && type != 0)
		{
			switch (type)
			{
				// enum dvar
			case 13:
				buffer->saveString(asset->enumDvarName);
				break;
				// newsticker
			case 20:
				buffer->align(Utils::Stream::ALIGN_4);
				buffer->save(asset->ticker);
				break;
				// textScrollDef
			case 21:
				buffer->align(Utils::Stream::ALIGN_4);
				buffer->save(asset->scroll);
				break;
			case 12:
				buffer->align(Utils::Stream::ALIGN_4);
				auto* destdef = buffer->dest<Game::multiDef_s>();
				buffer->save(asset->multi);

				for (int i = 0; i < 32; ++i)
				{
					if (asset->multi->dvarList[i])
					{
						buffer->saveString(asset->multi->dvarList[i]);
						Utils::Stream::ClearPointer(&destdef->dvarList[i]);
					}
				}

				for (int i = 0; i < 32; ++i)
				{
					if (asset->multi->dvarStr[i])
					{
						buffer->saveString(asset->multi->dvarStr[i]);
						Utils::Stream::ClearPointer(&destdef->dvarStr[i]);
					}
				}

				break;
			}
		}
		// editFieldDef
		else
		{
			buffer->align(Utils::Stream::ALIGN_4);
			buffer->save(asset->editField);
		}

		Utils::Stream::ClearPointer(&dest->typeData.data);

#ifdef WRITE_LOGS
		buffer->leaveStruct();
#endif
	}

	void ImenuDef_t::save_itemDef_s(Game::itemDef_s *asset, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::itemDef_s, 0x17C);

		Utils::Stream* buffer = builder->getBuffer();
		auto* dest = buffer->dest<Game::itemDef_s>();

#ifdef WRITE_LOGS
		if (asset->window.name)
			buffer->enterStruct(Utils::String::VA("itemDef_s: name = '%s'", asset->window.name));
		else if (asset->window.background)
			buffer->enterStruct(Utils::String::VA("itemDef_s: bg = '%s'", asset->window.background->info.name));
		else 
			buffer->enterStruct("itemDef_s");
#endif

		buffer->save(asset);

		// window data
		save_windowDef_t<Game::itemDef_s>(&asset->window, dest, builder);

		// text
		if (asset->text)
		{
			buffer->saveString(asset->text);
			Utils::Stream::ClearPointer(&dest->text);
		}

		// MenuEventHandlerSets
		EVENTHANDLERSET(mouseEnterText);
		EVENTHANDLERSET(mouseExitText);
		EVENTHANDLERSET(mouseEnter);
		EVENTHANDLERSET(mouseExit);
		EVENTHANDLERSET(action);
		EVENTHANDLERSET(accept);
		EVENTHANDLERSET(onFocus);
		EVENTHANDLERSET(leaveFocus);

		// Dvar strings
		if (asset->dvar)
		{
			buffer->saveString(asset->dvar);
			Utils::Stream::ClearPointer(&dest->dvar);
		}

		if (asset->dvarTest)
		{
			buffer->saveString(asset->dvarTest);
			Utils::Stream::ClearPointer(&dest->dvarTest);
		}

		// ItemKeyHandler
		if (asset->onKey)
		{
			buffer->align(Utils::Stream::ALIGN_4);
			this->save_ItemKeyHandler(asset->onKey, builder);
			Utils::Stream::ClearPointer(&dest->onKey);
		}

		// Dvar strings
		if (asset->enableDvar)
		{
			buffer->saveString(asset->enableDvar);
			Utils::Stream::ClearPointer(&dest->enableDvar);
		}

		if (asset->localVar)
		{
			buffer->saveString(asset->localVar);
			Utils::Stream::ClearPointer(&dest->localVar);
		}

		// Focus sound
		if (asset->focusSound)
		{
			dest->focusSound = builder->saveSubAsset(Game::XAssetType::ASSET_TYPE_SOUND, asset->focusSound).sound;
		}

		// itemDefData
		if (asset->typeData.data)
		{
			this->save_itemDefData_t(&asset->typeData, asset->type, dest, builder);
		}

		// floatExpressions
		if (asset->floatExpressions)
		{
			buffer->align(Utils::Stream::ALIGN_4);
#ifdef WRITE_LOGS
			buffer->enterStruct("floatExpressions");
#endif

			auto* destExp = buffer->dest<Game::ItemFloatExpression>();
			buffer->saveArray(asset->floatExpressions, asset->floatExpressionCount);

			for (int i = 0; i < asset->floatExpressionCount; ++i)
			{
				buffer->align(Utils::Stream::ALIGN_4);
				this->save_Statement_s(asset->floatExpressions[i].expression, builder);
				Utils::Stream::ClearPointer(&destExp[i].expression);
			}

			Utils::Stream::ClearPointer(&dest->floatExpressions);

#ifdef WRITE_LOGS
			buffer->leaveStruct();
#endif
		}

		// Statements
		STATEMENT(visibleExp);
		STATEMENT(disabledExp);
		STATEMENT(textExp);
		STATEMENT(materialExp);

#ifdef WRITE_LOGS
		buffer->leaveStruct();
#endif
	}

	void ImenuDef_t::save(Game::XAssetHeader header, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::menuDef_t, 400);
		AssertSize(Game::windowDef_t, 0xA4);

#ifdef WRITE_LOGS
		buffer->enterStruct("ImenuDef_t");
#endif

		Utils::Stream* buffer = builder->getBuffer();
		auto* asset = header.menu;
		auto* dest = buffer->dest<Game::menuDef_t>();
		buffer->save(asset);

		buffer->pushBlock(Game::XFILE_BLOCK_VIRTUAL);

		// ExpressionSupportingData
		if (asset->expressionData)
		{
			//if (builder->hasPointer(asset->expressionData))
			//{
			//	dest->expressionData = builder->getPointer(asset->expressionData);
			//}
			//else
			{
				this->save_ExpressionSupportingData(asset->expressionData, builder);
				Utils::Stream::ClearPointer(&dest->expressionData);
			}
		}

		// Window data
		save_windowDef_t<Game::menuDef_t>(&asset->window, dest, builder);

		// Font
		if (asset->font)
		{
			buffer->saveString(asset->font);
			Utils::Stream::ClearPointer(&dest->font);
		}

		// MenuEventHandlerSets
		EVENTHANDLERSET(onOpen);
		EVENTHANDLERSET(onCloseRequest);
		EVENTHANDLERSET(onClose);
		EVENTHANDLERSET(onESC);

		// ItemKeyHandler
		if (asset->onKey)
		{
			buffer->align(Utils::Stream::ALIGN_4);
			this->save_ItemKeyHandler(asset->onKey, builder);
			Utils::Stream::ClearPointer(&dest->onKey);
		}

		// Statement
		STATEMENT(visibleExp);

		// Strings
		if (asset->allowedBinding)
		{
			buffer->saveString(asset->allowedBinding);
			Utils::Stream::ClearPointer(&dest->allowedBinding);
		}
		if (asset->soundName)
		{
			buffer->saveString(asset->soundName);
			Utils::Stream::ClearPointer(&dest->soundName);
		}

		// Statements
		STATEMENT(rectXExp);
		STATEMENT(rectYExp);
		STATEMENT(rectHExp);
		STATEMENT(rectWExp);
		STATEMENT(openSoundExp);
		STATEMENT(closeSoundExp);

		// Items
		if (asset->items)
		{
			buffer->align(Utils::Stream::ALIGN_4);
			buffer->saveArray(asset->items, asset->itemCount);

			for (int i = 0; i < asset->itemCount; ++i)
			{
				if (asset->items[i])
				{
					buffer->align(Utils::Stream::ALIGN_4);
					this->save_itemDef_s(asset->items[i], builder);
				}
			}
		}
#ifdef WRITE_LOGS
		buffer->leaveStruct();
#endif

		buffer->popBlock();
	}
}
