#include "ArenaLength.hpp"
#include "GSC/Script.hpp"

namespace Components
{
	std::recursive_mutex Localization::LocalizeMutex;
	Dvar::Var Localization::UseLocalization;
	std::unordered_map<std::string, Game::LocalizeEntry*> Localization::LocalizeMap;

	std::optional<std::string> Localization::PrefixOverride;
	std::function<void(Game::LocalizeEntry*)> Localization::ParseCallback;

	void Localization::Set(const std::string& psLocalReference, const std::string& psNewString)
	{
		std::lock_guard _(LocalizeMutex);
		Utils::Memory::Allocator* allocator = Utils::Memory::GetAllocator();

		auto key = psLocalReference;
		if (PrefixOverride.has_value())
		{
			key.insert(0, PrefixOverride.value());
		}

		if (LocalizeMap.contains(key))
		{
			auto* entry = LocalizeMap[key];

			const auto* newStaticValue = allocator->duplicateString(psNewString);
			if (!newStaticValue) return;

			if (entry->value) allocator->free(entry->value);
			entry->value = newStaticValue;

			SaveParseOutput(entry);

			return;
		}

		auto* entry = allocator->allocate<Game::LocalizeEntry>();
		if (!entry) return;

		entry->name = allocator->duplicateString(key);
		if (!entry->name)
		{
			allocator->free(entry);
			return;
		}

		entry->value = allocator->duplicateString(psNewString);
		if (!entry->value)
		{
			allocator->free(entry->name);
			allocator->free(entry);
			return;
		}

		SaveParseOutput(entry);

		LocalizeMap[key] = entry;
	}

	const char* Localization::Get(const char* key)
	{
		if (!UseLocalization.get<bool>()) return key;

		Game::LocalizeEntry* entry = nullptr;

		{
			std::lock_guard _(LocalizeMutex);

			if (LocalizeMap.contains(key))
			{
				entry = LocalizeMap[key];
			}
		}

		if (!entry || !entry->value)
		{
			entry = Game::DB_FindXAssetHeader(Game::XAssetType::ASSET_TYPE_LOCALIZE_ENTRY, key).localize;
		}

		if (entry && entry->value)
		{
			return entry->value;
		}

		return key;
	}

	void __stdcall Localization::SetStringStub(const char* psLocalReference, const char* psNewString, [[maybe_unused]] int bSentenceIsEnglish)
	{
		Set(psLocalReference, psNewString);
	}

	void Localization::ParseOutput(const std::function<void(Game::LocalizeEntry*)>& callback)
	{
		ParseCallback = callback;
	}

	void Localization::SaveParseOutput(Game::LocalizeEntry* asset)
	{
		if (ParseCallback)
		{
			ParseCallback(asset);
		}
	}

	void Localization::SetCredits()
	{
		static const char* staff[] =
		{
			"Snake",
			"/dev/../",
			"/dev/console",
			"/dev/full",
			"/dev/sdb",
			"/dev/sr0",
			"/dev/tty0",
			"/dev/urandom",
			"Dss0",
			"Evan/Eve",
			"FutureRave",
			"H3X1C",
			"Homura",
			"Laupetin",
			"Louvenarde",
			"lsb_release -a",
			"quaK",
		};

		static const char* contributors[] =
		{
			"a231",
			"AmateurHailbut",
			"Aoki",
			"Chase",
			"civil",
			"Dasfonia",
			"Deity",
			"Dizzy",
			"HardNougat",
			"INeedGames",
			"JTAG",
			"Killera",
			"Lithium",
			"OneFourOne",
			"RaidMax",
			"Revo",
			"RezTech",
			"Shadow the Hedgehog",
			"Slykuiper",
			"st0rm",
			"VVLNT",
			"X3RX35",
		};

		static const char* specials[] =
		{
			"NTAuthority",
			"aerosoul94",
			"ReactIW4",
			"IW4Play",
			"V2",
			"luckyy"
		};

		std::string credits = "^2The IW4x Team:^7\n";

		for (std::size_t i = 0; i < ARRAYSIZE(staff); ++i)
		{
			credits.append(staff[i]);
			credits.append("\n");
		}

		credits.append("\n^3Contributors:^7\n");

		for (std::size_t i = 0; i < ARRAYSIZE(contributors); ++i)
		{
			credits.append(contributors[i]);
			credits.append("\n");
		}

		credits.append("\n^5Special thanks to:^7\n");

		for (std::size_t i = 0; i < ARRAYSIZE(specials); ++i)
		{
			credits.append(specials[i]);
			credits.append("\n");
		}

		// I have no idea why, but the last 2 lines are invisible!
		credits.append("-\n-");

		Set("IW4X_CREDITS", credits);
	}

	const char* Localization::SEH_LocalizeTextMessageStub(const char* pszInputBuffer, const char* pszMessageType, Game::msgLocErrType_t errType)
	{
		constexpr auto szStringCount = 10;
		constexpr auto szStringSize = 1024;

		char szInsertBuf[szStringSize];
		char szTokenBuf[szStringSize];

		static thread_local int iCurrString;
		static thread_local char szStrings[szStringCount][szStringSize];

		iCurrString = (iCurrString + 1) % szStringCount;
		std::memset(szStrings[iCurrString], 0, sizeof(szStrings[0]));
		auto* pszString = szStrings[iCurrString];
		auto iLen = 0;
		auto bLocOn = 1;
		auto bInsertEnabled = 1;
		auto iInsertLevel = 0;
		auto insertIndex = 1;
		auto bLocSkipped = 0;
		const auto* pszTokenStart = pszInputBuffer;
		const auto* pszIn = pszInputBuffer;

		auto i = 0;
		while (*pszTokenStart)
		{
			if (*pszIn && *pszIn != '\x14' && *pszIn != '\x15' && *pszIn != '\x16')
			{
				++pszIn;
				continue;
			}

			if (pszIn > pszTokenStart)
			{
				auto iTokenLen = pszIn - pszTokenStart;
				Game::I_strncpyz_s(szTokenBuf, sizeof(szTokenBuf), pszTokenStart, pszIn - pszTokenStart);
				if (bLocOn)
				{
					if (!Game::SEH_GetLocalizedTokenReference(szTokenBuf, szTokenBuf, pszMessageType, errType))
					{
						return nullptr;
					}

					iTokenLen = std::strlen(szTokenBuf);
				}

				if (iTokenLen + iLen >= szStringSize)
				{
					Game::Com_Printf(Game::CON_CHANNEL_SYSTEM, "%s too long when translated\n", pszMessageType);
					return nullptr;
				}

				for (i = 0; i < iTokenLen - 2; ++i)
				{
					if (!std::strncmp(&szTokenBuf[i], "&&", 2) && std::isdigit(static_cast<unsigned char>(szTokenBuf[i + 2])))
					{
						if (bInsertEnabled)
						{
							++iInsertLevel;
						}
						else
						{
							szTokenBuf[i] = '\x16';
							bLocSkipped = 1;
						}
					}
				}

				if (iInsertLevel <= 0 || iLen <= 0)
				{
					Game::I_strcpy(&pszString[iLen], szStringSize - iLen, szTokenBuf);
				}
				else
				{
					for (i = 0; i < iLen - 2; ++i)
					{
						if (!std::strncmp(&pszString[i], "&&", 2) && std::isdigit(static_cast<unsigned char>(pszString[i + 2])))
						{
							const auto digit = pszString[i + 2] - 48;
							if (!digit)
							{
								Game::Com_Printf(Game::CON_CHANNEL_SYSTEM, "%s cannot have &&0 as conversion format: \"%s\"\n", pszMessageType, pszInputBuffer);
							}
							if (digit == insertIndex)
							{
								Game::I_strcpy(szInsertBuf, sizeof(szInsertBuf), &pszString[i + 3]);
								pszString[i] = 0;
								++insertIndex;
								break;
							}
						}
					}

					Game::I_strcpy(&pszString[i], szStringSize - i, szTokenBuf);
					Game::I_strcpy(&pszString[iTokenLen + i], szStringSize - (iTokenLen + i), szInsertBuf);

					iLen -= 3;
					--iInsertLevel;
				}

				iLen += iTokenLen;
			}

			bInsertEnabled = 1;
			if (*pszIn == '\x14')
			{
				bLocOn = 1;
				++pszIn;
			}
			else if (*pszIn == '\x15')
			{
				bLocOn = 0;
				++pszIn;
			}

			if (*pszIn == '\x16')
			{
				bInsertEnabled = 0;
				++pszIn;
			}

			pszTokenStart = pszIn;
		}

		if (bLocSkipped)
		{
			for (i = 0; i < iLen; ++i)
			{
				if (pszString[i] == '\x16')
				{
					pszString[i] = '%';
				}
			}
		}

		return pszString;
	}

	const char* Localization::LocalizeMapName(const char* mapName)
	{
		for (int i = 0; i < *Game::arenaCount; ++i)
		{
			if (!_stricmp(ArenaLength::NewArenas[i].mapName, mapName))
			{
				auto* uiName = &ArenaLength::NewArenas[i].uiName[0];
				if ((uiName[0] == 'M' && uiName[1] == 'P') || (uiName[0] == 'P' && uiName[1] == 'A')) // MPUI/PATCH
				{
					return Get(uiName);
				}

				return uiName;
			}
		}

		return mapName;
	}

	void Localization::GSCr_LocalizeText()
	{
		if (Game::Scr_GetNumParam() != 1)
		{
			Game::Scr_Error("GSCr_LocalizeText: missing key!");
			return;
		}

		const char* str = Game::Scr_GetString(0);

		const auto result = Game::UI_SafeTranslateString(str);

		Game::Scr_AddString(result);
	}

	void Localization::GSCr_LocalizeGametype()
	{
		if (Game::Scr_GetNumParam() != 1)
		{
			Game::Scr_Error("GSCr_LocalizeGametype: missing gametype!");
			return;
		}

		const char* gametype = Game::Scr_GetString(0);

		// UI_GetGameTypeDisplayName
		const auto result = Utils::Hook::Call<const char* (const char*)>(0x4EB0B0)(gametype);

		Game::Scr_AddString(result);
	}


	Localization::Localization()
	{
		SetCredits();

		AssetHandler::OnFind(Game::XAssetType::ASSET_TYPE_LOCALIZE_ENTRY, [](Game::XAssetType, const std::string& name)
		{
			Game::XAssetHeader header = { nullptr };
			std::lock_guard _(LocalizeMutex);

			if (const auto itr = LocalizeMap.find(name); itr != LocalizeMap.end())
			{
				header.localize = itr->second;
			}

			return header;
		});

		// Resolving hook
		Utils::Hook(0x629B90, Get, HOOK_JUMP).install()->quick();

		// Overwrite SetString
		Utils::Hook(0x4CE5EE, SetStringStub, HOOK_CALL).install()->quick();

		Utils::Hook(0x49D4A0, SEH_LocalizeTextMessageStub, HOOK_JUMP).install()->quick();
		Utils::Hook::Nop(0x49D4A5, 1);

		UseLocalization = Dvar::Register<bool>("ui_localize", true, Game::DVAR_NONE, "Use localization strings");

		// Generate localized entries for custom classes above 10
		AssetHandler::OnLoad([](Game::XAssetType type, Game::XAssetHeader asset, const std::string& name, bool* /*restrict*/)
		{
			if (type != Game::XAssetType::ASSET_TYPE_LOCALIZE_ENTRY) return;

			if (name == "CLASS_SLOT1"s)
			{
				for (int i = 11; i <= NUM_CUSTOM_CLASSES; ++i)
				{
					std::string key = Utils::String::VA("CLASS_SLOT%i", i);

					std::string value = asset.localize->value;
					Utils::String::Replace(value, "1", std::to_string(i)); // Pretty ugly, but it should work

					Set(key, value);
				}
			}
		});

		// gsc: LocalizeText(key)  (e.g. MP_MIDDLE_SQUAD)
		Components::GSC::Script::AddFunction("LocalizeText", GSCr_LocalizeText);

		// gsc: LocalizeGametype(gametype)  (e.g.: dm, war, koth)
		Components::GSC::Script::AddFunction("LocalizeGametype", GSCr_LocalizeGametype);
	}

	Localization::~Localization()
	{
		LocalizeMap.clear();
	}
}
