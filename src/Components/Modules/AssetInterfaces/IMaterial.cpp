#include "STDInclude.hpp"

#define IW4X_MAT_VERSION "1"

namespace Assets
{
	static const char* techsetSuffix[] =
	{
		"_lin",
		"_add_lin",
		"_replace",
		"_eyeoffset",

		"_blend",
		"_blend_nofog",
		"_add",
		"_nofog",
		"_nocast",

		"_add_lin_nofog",
	};

	std::map<std::string, std::string> techSetCorrespondance = {
		{"effect", "effect_blend"},
		{"effect", "effect_blend"},
		{"effect_nofog", "effect_blend_nofog"},
		{"effect_zfeather", "effect_zfeather_blend"},

		{"wc_unlit_add", "wc_unlit_add_lin"},
		{"wc_unlit_distfalloff", "wc_unlit_distfalloff_replace"},
		{"wc_unlit_multiply", "wc_unlit_multiply_lin"},
		{"wc_unlit_falloff_add", "wc_unlit_falloff_add_lin_ua"},
		{"wc_unlit", "wc_unlit_replace_lin"},
		{"wc_unlit_alphatest", "wc_unlit_blend_lin"},
		{"wc_unlit_multiply_lin", "wc_unlit_multiply_lin"},
		{"wc_unlit_blend", "wc_unlit_blend_lin_ua"},
		{"wc_unlit_replace", "wc_unlit_replace_lin"},

		{"mc_unlit_replace", "mc_unlit_replace_lin"},
		{"mc_unlit_nofog", "mc_unlit_blend_nofog_ua"},
		{"mc_unlit", "mc_unlit_blend_lin"},
		{"mc_unlit_alphatest", "mc_unlit_blend_lin"}
		/*,
		{"", ""},
		{"", ""},
		{"", ""},
		{"", ""},
		{"", ""},*/
	};

	void IMaterial::load(Game::XAssetHeader* header, const std::string& name, Components::ZoneBuilder::Zone* builder)
	{
		if (!header->data) this->loadJson(header, name, builder);   // Check if we want to override materials
		if (!header->data) this->loadOverride(header, name, builder);   // Check if we want to override materials
		if (!header->data) this->loadNative(header, name, builder); // Check if there is a native one
		if (!header->data) this->loadBinary(header, name, builder); // Check if we need to import a new one into the game
	}

	void IMaterial::dump(Game::XAssetHeader header)
	{
		Game::Material* material = header.material;

		std::string buffer;

		auto constantTable = json11::Json::array{};
		for (char i = 0; i < material->constantCount; i++)
		{
			auto literals = json11::Json::array(4);
			for (char literalIndex = 0; literalIndex < 4; literalIndex++)
			{
				literals[literalIndex] = material->constantTable[i].literal[literalIndex];
			}

			constantTable.push_back(json11::Json::object{
				{"literals", literals},
				{"name", material->constantTable[i].name},
				{"nameHash", static_cast<int>(material->constantTable[i].nameHash)}
			});
		}

		auto textureTable = json11::Json::array{};
		for (char i = 0; i < material->textureCount; i++)
		{
			auto texture = material->textureTable[i];
			auto imageName = texture.u.image->name;
			bool hasWater = false;
			json11::Json::object jsonWater{};

			if (texture.semantic == SEMANTIC_WATER_MAP)
			{
				if (texture.u.water)
				{
					Game::water_t* water = texture.u.water;
					hasWater = true;

					imageName = water->image->name;

					jsonWater["floatTime"] = water->writable.floatTime;
					auto codeConstants = json11::Json::array{};
					for (size_t j = 0; j < 4; j++)
					{
						codeConstants.push_back(water->codeConstant[j]);
					}

					jsonWater["codeConstant"] = codeConstants;

					jsonWater["M"] = water->M;
					jsonWater["N"] = water->N;
					jsonWater["Lx"] = water->Lx;
					jsonWater["Lz"] = water->Lz;
					jsonWater["gravity"] = water->gravity;
					jsonWater["windvel"] = water->windvel;

					auto windDirection = json11::Json::array{ water->winddir[0],  water->winddir[1]};

					jsonWater["winddir"] = windDirection;
					jsonWater["amplitude"] = water->amplitude;

					json11::Json::array waterComplexData{};
					json11::Json::array wTerm{};

					for (int j = 0; j < water->M * water->N; j++)
					{
						json11::Json::object complexdata{};
						json11::Json::array curWTerm{};

						complexdata["real"] = water->H0[j].real;
						complexdata["imag"] = water->H0[j].imag;

						curWTerm[j] = water->wTerm[j];

						waterComplexData[j] = complexdata;
					}

					jsonWater["complex"] = waterComplexData;
					jsonWater["wTerm"] = wTerm;
				}
			}

			auto jsonTexture = json11::Json::object{
				{ "image", imageName },
				{ "firstCharacter", texture.nameStart },
				{ "lastCharacter", texture.nameEnd },
				{ "firstCharacter", texture.u.image->name[0] },
				{ "sampleState", texture.samplerState },
				{ "semantic", texture.semantic },
				{ "nameHash", static_cast<int>(texture.nameHash) }
			};

			if (hasWater) {
				jsonTexture["waterinfo"] = jsonWater;
			}

			textureTable.push_back(jsonTexture);

			auto image = Game::DB_FindXAssetEntry(Game::XAssetType::ASSET_TYPE_IMAGE, imageName);
			if (image) 
			{
				Components::AssetHandler::Dump(Game::DB_FindXAssetEntry(Game::XAssetType::ASSET_TYPE_IMAGE, imageName)->asset);
			}
			else {
				Components::Logger::Error(0, "Error while dumping %s, could not dump the associated image (%s) because FindXAssetEntry failed!", material->info.name, imageName);
			}
		}


		auto stateMap = json11::Json::array{};
		for (char i = 0; i < material->stateBitsCount; i++)
		{
			stateMap.push_back(
				json11::Json::array{ 
					static_cast<int>(material->stateBitsTable[i].loadBits[0]),
					static_cast<int>(material->stateBitsTable[i].loadBits[1])
				}
			);
		}

		json11::Json matData = json11::Json::object{
			{ "name",  material->info.name },
			{ "techniqueSet->name", material->techniqueSet->name },
			{ "gameFlags", material->info.gameFlags },
			{ "sortKey", material->info.sortKey },
			{ "animationX", material->info.textureAtlasColumnCount },
			{ "animationY", material->info.textureAtlasRowCount },
			{ "cameraRegion", material->cameraRegion },
			{ "constantTable", constantTable},
			{ "maps", textureTable},
			{ "stateMap", stateMap},
			{ "stateFlags", material->stateFlags },
			{ "surfaceTypeBits", static_cast<int>(material->info.surfaceTypeBits) },
			{ "unknown", static_cast<int>(material->info.drawSurf.packed) } // :/ should be unsigned long long but json doesn't let us... maybe we should make it a string?
		};

		matData.dump(buffer);
		Utils::IO::WriteFile(Utils::String::VA("dump/materials/%s.json", material->info.name), buffer);
	}

	bool IMaterial::findMatchingTechset(Game::Material* asset, std::string techsetName, Components::ZoneBuilder::Zone* builder) {
		if (!techsetName.empty() && techsetName.front() == ',') techsetName.erase(techsetName.begin());
		asset->techniqueSet = Components::AssetHandler::FindAssetForZone(Game::XAssetType::ASSET_TYPE_TECHNIQUE_SET, techsetName.data(), builder).techniqueSet;

		///
		/// Case 1: The exact same techset already exists in iw4, we reuse it
		/// 
		if (asset->techniqueSet)
		{
#if DEBUG
			Components::Logger::Print("Techset %s exists with the same name in iw4, and was mapped 1:1 with %s\n", techsetName.data(), asset->techniqueSet->name);
#endif
			// Do we need to remap the sortkey if the techset is already correct?
			// ... maybe?
			//findSortKey(asset, builder);

			return true;
		}

		///
		/// Case 2: The name is slightly different (nofog suffix and others)
		/// 
		std::string suffix;
		if (Utils::String::StartsWith(techsetName, "effect_") && Utils::String::EndsWith(techsetName, "_nofog"))
		{
			suffix = "_nofog";
			Utils::String::Replace(techsetName, suffix, "");
		}

		for (int i = 0; i < ARRAYSIZE(techsetSuffix); ++i)
		{
			Game::MaterialTechniqueSet* techsetPtr = Components::AssetHandler::FindAssetForZone(Game::XAssetType::ASSET_TYPE_TECHNIQUE_SET, (techsetName + techsetSuffix[i] + suffix).data(), builder).techniqueSet;

			if (techsetPtr)
			{
				asset->techniqueSet = techsetPtr;

				if (asset->techniqueSet->name[0] == ',') continue; // Try to find a better one
				Components::Logger::Print("Techset '%s' has been mapped to '%s'\n", techsetName.data(), asset->techniqueSet->name);

				findSortKey(asset);

				return true;
			}
		}

		///
		/// Case 3: We know an equivalent that works well
		/// 
		static thread_local bool replacementFound;
		std::string techName = asset->techniqueSet->name;
		if (techSetCorrespondance.find(techName) != techSetCorrespondance.end()) {
			auto iw4TechSetName = techSetCorrespondance[techName];
			Game::XAssetEntry* iw4TechSet = Game::DB_FindXAssetEntry(Game::XAssetType::ASSET_TYPE_TECHNIQUE_SET, iw4TechSetName.data());

			if (iw4TechSet)
			{
				Game::DB_EnumXAssetEntries(Game::XAssetType::ASSET_TYPE_MATERIAL, [asset, iw4TechSet](Game::XAssetEntry* entry)
					{
						if (!replacementFound)
						{
							Game::XAssetHeader header = entry->asset.header;

							if (header.material->techniqueSet == iw4TechSet->asset.header.techniqueSet)
							{
								Components::Logger::Print("Material %s with techset %s has been mapped to %s (last chance!), taking the sort key of material %s\n", asset->info.name, asset->techniqueSet->name, header.material->techniqueSet->name, header.material->info.name);
								asset->info.sortKey = header.material->info.sortKey;
								asset->techniqueSet = iw4TechSet->asset.header.techniqueSet;

								// this is terrible!
								asset->stateBitsCount = header.material->stateBitsCount;
								asset->stateBitsTable = header.material->stateBitsTable;
								std::memcpy(asset->stateBitsEntry, header.material->stateBitsEntry, 48);
								asset->constantCount = header.material->constantCount;
								asset->constantTable = header.material->constantTable;

								replacementFound = true;
							}
						}
					}, false, false);

				if (replacementFound)
				{
					return true;
				}
				else
				{
					Components::Logger::Print("Could not find any loaded material with techset %s (in replacement of %s), so I cannot set the sortkey for material %s\n", iw4TechSetName.data(), asset->techniqueSet->name, asset->info.name);
				}
			}
			else
			{
				Components::Logger::Print("Could not find any loaded techset with iw4 name %s for iw3 techset %s\n", iw4TechSetName.data(), asset->techniqueSet->name);
			}
		}
		else
		{
			Components::Logger::Print("Could not match iw3 techset %s with any of the techsets I know! This is a critical error, there's a good chance the map will not be playable.\n", techName.data());
		}

		return false;
	}

	bool IMaterial::findSortKey(Game::Material* asset)
	{
		static thread_local bool replacementFound = false;

		Game::DB_EnumXAssetEntries(Game::XAssetType::ASSET_TYPE_MATERIAL, [asset](Game::XAssetEntry* entry)
			{
				if (!replacementFound)
				{
					Game::XAssetHeader header = entry->asset.header;

					const char* name = asset->techniqueSet->name;
					if (name[0] == ',') ++name;

					// Found another material with the same techset name!
					if (std::string(name) == header.material->techniqueSet->name)
					{
						asset->info.sortKey = header.material->info.sortKey;

						// This is temp, as nobody has time to fix materials
						asset->stateBitsCount = header.material->stateBitsCount;
						asset->stateBitsTable = header.material->stateBitsTable;
						std::memcpy(asset->stateBitsEntry, header.material->stateBitsEntry, 48);
						asset->constantCount = header.material->constantCount;
						asset->constantTable = header.material->constantTable;

						Components::Logger::Print("Material %s with techset %s has been set to the same sortkey and statebits as %s (%d)\n", asset->info.name, asset->techniqueSet->name, header.material->techniqueSet->name, header.material->info.sortKey);

						replacementFound = true;
					}
				}
			}, false, false);

		if (replacementFound) {
			return true;
		}

		auto techsetMatches = [](Game::Material* m1, Game::Material* m2)
		{
			Game::MaterialTechniqueSet* t1 = m1->techniqueSet;
			Game::MaterialTechniqueSet* t2 = m2->techniqueSet;
			if (!t1 || !t2) return false;

			// Found another material with the same remapped techset name!
			if (t1->remappedTechniqueSet && t2->remappedTechniqueSet && std::string(t1->remappedTechniqueSet->name) == t2->remappedTechniqueSet->name) return true;

			for (int i = 0; i < ARRAYSIZE(t1->techniques); ++i)
			{
				if (!t1->techniques[i] && !t2->techniques[i]) continue;;
				if (!t1->techniques[i] || !t2->techniques[i]) return false;

				// Apparently, this is really not that important
				//if (t1->techniques[i]->flags != t2->techniques[i]->flags) return false; 
			}

			return true;
		};


		Game::DB_EnumXAssetEntries(Game::XAssetType::ASSET_TYPE_MATERIAL, [asset, techsetMatches](Game::XAssetEntry* entry)
			{
				if (!replacementFound)
				{
					Game::XAssetHeader header = entry->asset.header;

					if (techsetMatches(header.material, asset))
					{
						Components::Logger::Print("Material %s with techset %s has been set to the same sortkey as %s (%d)\n", asset->info.name, asset->techniqueSet->name, header.material->techniqueSet->name, header.material->info.sortKey);
						asset->info.sortKey = header.material->info.sortKey;
						asset->stateBitsCount = header.material->stateBitsCount;
						asset->stateBitsTable = header.material->stateBitsTable;
						std::memcpy(asset->stateBitsEntry, header.material->stateBitsEntry, 48);
						asset->constantCount = header.material->constantCount;
						asset->constantTable = header.material->constantTable;

						replacementFound = true;
					}
				}
			}, false, false);

		if (!replacementFound)
		{
			Components::Logger::Print("Material %s with techset %s could not be matched to an existing material, and will keep its sortkey, valid or not (%d)\n", asset->info.name, asset->techniqueSet->name, asset->info.sortKey);
		}

		return replacementFound;
	}

	void IMaterial::loadBinary(Game::XAssetHeader* header, const std::string& name, Components::ZoneBuilder::Zone* builder)
	{

		Components::FileSystem::File materialFile(Utils::String::VA("materials/%s.iw4xMaterial", name.data()));
		if (!materialFile.exists()) return;

		Utils::Stream::Reader reader(builder->getAllocator(), materialFile.getBuffer());

		char* magic = reader.readArray<char>(7);
		if (std::memcmp(magic, "IW4xMat", 7))
		{
			Components::Logger::Error(0, "Reading material '%s' failed, header is invalid!", name.data());
		}

		std::string version;
		version.push_back(reader.read<char>());
		if (version != IW4X_MAT_VERSION)
		{
			Components::Logger::Error("Reading material '%s' failed, expected version is %d, but it was %d!", name.data(), atoi(IW4X_MAT_VERSION), atoi(version.data()));
		}

		Game::Material* asset = reader.readObject<Game::Material>();

		if (asset->info.name)
		{
			asset->info.name = reader.readCString();
		}

		if (asset->techniqueSet)
		{
			findMatchingTechset(asset, reader.readCString(), builder);
		}

		if (asset->textureTable)
		{
			asset->textureTable = reader.readArray<Game::MaterialTextureDef>(asset->textureCount);

			for (char i = 0; i < asset->textureCount; ++i)
			{
				Game::MaterialTextureDef* textureDef = &asset->textureTable[i];

				if (textureDef->semantic == SEMANTIC_WATER_MAP)
				{
					if (textureDef->u.water)
					{
						Game::water_t* water = reader.readObject<Game::water_t>();
						textureDef->u.water = water;

						// Save_water_t
						if (water->H0)
						{
							water->H0 = reader.readArray<Game::complex_s>(water->M * water->N);
						}

						if (water->wTerm)
						{
							water->wTerm = reader.readArray<float>(water->M * water->N);
						}

						if (water->image)
						{
							water->image = Components::AssetHandler::FindAssetForZone(Game::XAssetType::ASSET_TYPE_IMAGE, reader.readString().data(), builder).image;
						}
					}
				}
				else if (textureDef->u.image)
				{
					textureDef->u.image = Components::AssetHandler::FindAssetForZone(Game::XAssetType::ASSET_TYPE_IMAGE, reader.readString().data(), builder).image;
				}
			}
		}

		if (asset->constantTable)
		{
			asset->constantTable = reader.readArray<Game::MaterialConstantDef>(asset->constantCount);
		}

		if (asset->stateBitsTable)
		{
			asset->stateBitsTable = reader.readArray<Game::GfxStateBits>(asset->stateBitsCount);
		}

		header->material = asset;

		if (!reader.end())
		{
			Components::Logger::Error("Material data left!");
		}

		/*char baseIndex = 0;
		for (char i = 0; i < asset->stateBitsCount; ++i)
		{
			auto stateBits = asset->stateBitsTable[i];
			if (stateBits.loadBits[0] == 0x18128812 &&
				stateBits.loadBits[1] == 0xD) // Seems to be like a default stateBit causing a 'generic' initialization
			{
				baseIndex = i;
				break;
			}
		}

		for (int i = 0; i < 48; ++i)
		{
			if (!asset->techniqueSet->techniques[i] && asset->stateBitsEntry[i] != -1)
			{
				asset->stateBitsEntry[i] = -1;
			}

			if (asset->techniqueSet->techniques[i] && asset->stateBitsEntry[i] == -1)
			{
				asset->stateBitsEntry[i] = baseIndex;
			}
		}*/
	}

	void IMaterial::loadNative(Game::XAssetHeader* header, const std::string& name, Components::ZoneBuilder::Zone* /*builder*/)
	{
		header->material = Components::AssetHandler::FindOriginalAsset(this->getType(), name.data()).material;
	}

	void IMaterial::loadJson(Game::XAssetHeader* header, const std::string& name, Components::ZoneBuilder::Zone* builder)
	{
		Components::FileSystem::File materialInfo(Utils::String::VA("materials/%s.json", name.data()));

		if (!materialInfo.exists())
		{
			// Zonetool doesn't use the JSON extension, despite the files being JSON :/
			materialInfo = Components::FileSystem::File(Utils::String::VA("materials/%s", name.data()));

			if (!materialInfo.exists())
			{
				return;
			}
		}

		std::string errors;
		json11::Json jsonMat = json11::Json::parse(materialInfo.getBuffer(), errors);

		if (!jsonMat.is_object())
		{
			Components::Logger::Error("Failed to load material information for %s!", name.data());
			return;
		}


		Game::Material* material = builder->getAllocator()->allocate<Game::Material>();

		if (!material)
		{
			Components::Logger::Error("Failed to allocate material structure!");
			return;
		}

		material->info.textureAtlasColumnCount = static_cast<char>(jsonMat["animationX"].int_value());
		material->info.textureAtlasRowCount = static_cast<char>(jsonMat["animationY"].int_value());
		material->cameraRegion = static_cast<char>(jsonMat["cameraRegion"].int_value());

		json11::Json::array jsonConstantTable = jsonMat["constantTable"].array_items();
		material->constantCount = static_cast<char>(jsonConstantTable.size());
		material->constantTable = builder->getAllocator()->allocateArray<Game::MaterialConstantDef>(material->constantCount);

		for (char i = 0; i < material->constantCount; i++)
		{
			for (size_t litteralIndex = 0; litteralIndex < 4; litteralIndex++)
			{
				material->constantTable[i].literal[litteralIndex] = static_cast<float>(jsonConstantTable[i]["literal"].array_items()[litteralIndex].number_value());
			}

			strncpy(material->constantTable[i].name, jsonConstantTable[i]["name"].string_value().c_str(), sizeof(Game::MaterialConstantDef::name));
			material->constantTable[i].nameHash = jsonConstantTable[i]["nameHash"].int_value();
		}

		material->info.gameFlags = static_cast<char>(jsonMat["gameFlags"].int_value());

		json11::Json::array jsonMaps = jsonMat["maps"].array_items();
		material->textureCount = static_cast<char>(jsonMaps.size());
		material->textureTable = builder->getAllocator()->allocateArray<Game::MaterialTextureDef>(material->textureCount);

		for (char i = 0; i < material->textureCount; i++)
		{
			auto imageName = jsonMaps[i]["image"].string_value().c_str();
			auto texture = &material->textureTable[i];
			texture->nameStart = static_cast<char>(jsonMaps[i]["firstCharacter"].int_value());
			texture->nameEnd = static_cast<char>(jsonMaps[i]["lastCharacter"].int_value());
			texture->u.image = Components::AssetHandler::FindAssetForZone(Game::XAssetType::ASSET_TYPE_IMAGE, imageName, builder).image;
			texture->samplerState = static_cast<char>(jsonMaps[i]["sampleState"].int_value());
			texture->semantic = static_cast<char>(jsonMaps[i]["semantic"].int_value());
			texture->nameHash = jsonMaps[i]["typeHash"].int_value();

			if (texture->semantic == SEMANTIC_WATER_MAP) 
			{
				if (jsonMaps[i]["waterinfo"].is_object()) 
				{
					auto jsonWater = jsonMaps[i]["waterinfo"];
					auto water = builder->getAllocator()->allocate<Game::water_t>();

					water->image->name = imageName;

					water->writable.floatTime = static_cast<float>(jsonWater["floatTime"].number_value());
					auto codeConstants = json11::Json::array{};
					for (size_t j = 0; j < 4; j++)
					{
						water->codeConstant[j] = static_cast<float>(jsonWater["codeConstant"].array_items()[j].number_value());
					}

					water->M = jsonWater["M"].int_value();
					water->N = jsonWater["N"].int_value();
					water->Lx = static_cast<float>(jsonWater["Lx"].number_value());
					water->Lz = static_cast<float>(jsonWater["Lz"].number_value());
					water->gravity = static_cast<float>(jsonWater["gravity"].number_value());
					water->windvel = static_cast<float>(jsonWater["windvel"].number_value());

					water->winddir[0] = static_cast<float>(jsonWater["winddir"].array_items()[0].number_value());
					water->winddir[1] = static_cast<float>(jsonWater["winddir"].array_items()[1].number_value());

					water->amplitude = static_cast<float>(jsonWater["amplitude"].number_value());

					auto count = jsonWater["M"].int_value() * jsonWater["N"].int_value();

					water->H0 = builder->getAllocator()->allocateArray<Game::complex_s>(count);

					for (int j = 0; j < count; j++)
					{
						water->wTerm[j] = static_cast<float>(jsonWater["wTerm"].array_items()[j].number_value());

						water->H0[j].real = static_cast<float>(jsonWater["complex"].array_items()[j]["real"].number_value());
						water->H0[j].imag = static_cast<float>(jsonWater["complex"].array_items()[j]["complex"].number_value());
					}


					texture->u.water = water;
				}
				else 
				{
					Components::Logger::Error("Invalid material! %s is expected to have water info for texture %s, but no 'waterinfo' object is described.", material->info.name, imageName);
				}
			}
		}

		material->info.name = builder->getAllocator()->duplicateString(jsonMat["name"].string_value());
		material->info.sortKey = static_cast<char>(jsonMat["sortKey"].int_value());
		material->stateFlags = static_cast<char>(jsonMat["stateFlags"].number_value());

		json11::Json::array jsonStateMap = jsonMat["stateMap"].array_items();
		material->stateBitsCount = static_cast<char>(jsonStateMap.size());
		material->stateBitsTable = builder->getAllocator()->allocateArray<Game::GfxStateBits>(material->stateBitsCount);

		for (char i = 0; i < material->stateBitsCount; i++)
		{
			material->stateBitsTable[i].loadBits[0] = jsonStateMap[i][0].int_value();
			material->stateBitsTable[i].loadBits[1] = jsonStateMap[i][1].int_value();
		}

		material->info.surfaceTypeBits = jsonMat["surfaceTypeBits"].int_value();

		auto tsName = jsonMat["techniqueSet->name"].string_value();
		findMatchingTechset(material, tsName, builder);

		material->info.drawSurf = Game::GfxDrawSurf{ static_cast<unsigned long long>(jsonMat["unknown"].int_value()) }; // i HATE this !  int getting cast at unsigned long long? This should be a string storage in the JSON !!

		header->material = material;
	}

	void IMaterial::loadOverride(Game::XAssetHeader* header, const std::string& name, Components::ZoneBuilder::Zone* builder)
	{
		Components::FileSystem::File materialInfo(Utils::String::VA("materials/%s.override", name.data()));

		if (!materialInfo.exists())
		{
			return;
		}

		std::string errors;
		json11::Json infoData = json11::Json::parse(materialInfo.getBuffer(), errors);

		if (!infoData.is_object())
		{
			Components::Logger::Error("Failed to load material information for %s!", name.data());
			return;
		}

		auto base = infoData["base"];

		if (!base.is_string())
		{
			Components::Logger::Error("No valid material base provided for %s!", name.data());
			return;
		}

		Game::Material* baseMaterial = Game::DB_FindXAssetHeader(Game::XAssetType::ASSET_TYPE_MATERIAL, base.string_value().data()).material;

		if (!baseMaterial) // TODO: Maybe check if default asset? Maybe not? You could still want to use the default one as base!?
		{
			Components::Logger::Error("Basematerial '%s' not found for %s!", base.string_value().data(), name.data());
			return;
		}

		Game::Material* material = builder->getAllocator()->allocate<Game::Material>();

		if (!material)
		{
			Components::Logger::Error("Failed to allocate material structure!");
			return;
		}

		// Copy base material to our structure
		std::memcpy(material, baseMaterial, sizeof(Game::Material));
		material->info.name = builder->getAllocator()->duplicateString(name);

		material->info.textureAtlasRowCount = 1;
		material->info.textureAtlasColumnCount = 1;

		// Load animation frames
		auto anims = infoData["anims"];
		if (anims.is_array())
		{
			auto animCoords = anims.array_items();

			if (animCoords.size() >= 2)
			{
				auto animCoordX = animCoords[0];
				auto animCoordY = animCoords[1];

				if (animCoordX.is_number())
				{
					material->info.textureAtlasColumnCount = static_cast<char>(animCoordX.number_value()) & 0xFF;
				}

				if (animCoordY.is_number())
				{
					material->info.textureAtlasRowCount = static_cast<char>(animCoordY.number_value()) & 0xFF;
				}
			}
		}

		// Model surface textures are special, they need a special order and whatnot
		bool replaceTexture = Utils::String::StartsWith(name, "mc/");
		if (replaceTexture)
		{
			Game::MaterialTextureDef* textureTable = builder->getAllocator()->allocateArray<Game::MaterialTextureDef>(baseMaterial->textureCount);
			std::memcpy(textureTable, baseMaterial->textureTable, sizeof(Game::MaterialTextureDef) * baseMaterial->textureCount);
			material->textureTable = textureTable;
			material->textureCount = baseMaterial->textureCount;
		}

		// Load referenced textures
		auto textures = infoData["textures"];
		if (textures.is_array())
		{
			std::vector<Game::MaterialTextureDef> textureList;

			for (auto& texture : textures.array_items())
			{
				if (!texture.is_array()) continue;
				if (textureList.size() >= 0xFF) break;

				auto textureInfo = texture.array_items();
				if (textureInfo.size() < 2) continue;

				auto map = textureInfo[0];
				auto image = textureInfo[1];
				if (!map.is_string() || !image.is_string()) continue;

				Game::MaterialTextureDef textureDef;

				textureDef.semantic = 0; // No water image
				textureDef.samplerState = -30;
				textureDef.nameEnd = map.string_value().back();
				textureDef.nameStart = map.string_value().front();
				textureDef.nameHash = Game::R_HashString(map.string_value().data());

				textureDef.u.image = Components::AssetHandler::FindAssetForZone(Game::XAssetType::ASSET_TYPE_IMAGE, image.string_value(), builder).image;

				if (replaceTexture)
				{
					bool applied = false;

					for (char i = 0; i < baseMaterial->textureCount; ++i)
					{
						if (material->textureTable[i].nameHash == textureDef.nameHash)
						{
							applied = true;
							material->textureTable[i].u.image = textureDef.u.image;
							break;
						}
					}

					if (!applied)
					{
						Components::Logger::Error(0, "Unable to find texture for map '%s' in %s!", map.string_value().data(), baseMaterial->info.name);
					}
				}
				else
				{
					textureList.push_back(textureDef);
				}
			}

			if (!replaceTexture)
			{
				if (!textureList.empty())
				{
					Game::MaterialTextureDef* textureTable = builder->getAllocator()->allocateArray<Game::MaterialTextureDef>(textureList.size());

					if (!textureTable)
					{
						Components::Logger::Error("Failed to allocate texture table!");
						return;
					}

					std::memcpy(textureTable, textureList.data(), sizeof(Game::MaterialTextureDef) * textureList.size());

					material->textureTable = textureTable;
				}
				else
				{
					material->textureTable = nullptr;
				}

				material->textureCount = static_cast<char>(textureList.size()) & 0xFF;
			}
		}

		header->material = material;
	}

	void IMaterial::mark(Game::XAssetHeader header, Components::ZoneBuilder::Zone* builder)
	{
		Game::Material* asset = header.material;

		if (asset->techniqueSet)
		{
			builder->loadAsset(Game::XAssetType::ASSET_TYPE_TECHNIQUE_SET, asset->techniqueSet);
		}

		if (asset->textureTable)
		{
			for (char i = 0; i < asset->textureCount; ++i)
			{
				if (asset->textureTable[i].u.image)
				{
					if (asset->textureTable[i].semantic == SEMANTIC_WATER_MAP)
					{
						if (asset->textureTable[i].u.water->image)
						{
							builder->loadAsset(Game::XAssetType::ASSET_TYPE_IMAGE, asset->textureTable[i].u.water->image);
						}
					}
					else
					{
						builder->loadAsset(Game::XAssetType::ASSET_TYPE_IMAGE, asset->textureTable[i].u.image);
					}
				}
			}
		}
	}

	void IMaterial::save(Game::XAssetHeader header, Components::ZoneBuilder::Zone* builder)
	{
		AssertSize(Game::Material, 96);

		Utils::Stream* buffer = builder->getBuffer();
		Game::Material* asset = header.material;
		Game::Material* dest = buffer->dest<Game::Material>();
		buffer->save(asset);

		buffer->pushBlock(Game::XFILE_BLOCK_VIRTUAL);

		if (asset->info.name)
		{
			buffer->saveString(builder->getAssetName(this->getType(), asset->info.name));
			Utils::Stream::ClearPointer(&dest->info.name);
		}

		if (asset->techniqueSet)
		{
			dest->techniqueSet = builder->saveSubAsset(Game::XAssetType::ASSET_TYPE_TECHNIQUE_SET, asset->techniqueSet).techniqueSet;
		}

		if (asset->textureTable)
		{
			AssertSize(Game::MaterialTextureDef, 12);

			// Pointer/Offset insertion is untested, but it worked in T6, so I think it's fine
			if (builder->hasPointer(asset->textureTable))
			{
				dest->textureTable = builder->getPointer(asset->textureTable);
			}
			else
			{
				buffer->align(Utils::Stream::ALIGN_4);
				builder->storePointer(asset->textureTable);

				Game::MaterialTextureDef* destTextureTable = buffer->dest<Game::MaterialTextureDef>();
				buffer->saveArray(asset->textureTable, asset->textureCount);

				for (char i = 0; i < asset->textureCount; ++i)
				{
					Game::MaterialTextureDef* destTextureDef = &destTextureTable[i];
					Game::MaterialTextureDef* textureDef = &asset->textureTable[i];

					if (textureDef->semantic == SEMANTIC_WATER_MAP)
					{
						AssertSize(Game::water_t, 68);

						Game::water_t* destWater = buffer->dest<Game::water_t>();
						Game::water_t* water = textureDef->u.water;

						if (water)
						{
							buffer->align(Utils::Stream::ALIGN_4);
							buffer->save(water);
							Utils::Stream::ClearPointer(&destTextureDef->u.water);

							// Save_water_t
							if (water->H0)
							{
								buffer->align(Utils::Stream::ALIGN_4);
								buffer->save(water->H0, 8, water->M * water->N);
								Utils::Stream::ClearPointer(&destWater->H0);
							}

							if (water->wTerm)
							{
								buffer->align(Utils::Stream::ALIGN_4);
								buffer->save(water->wTerm, 4, water->M * water->N);
								Utils::Stream::ClearPointer(&destWater->wTerm);
							}

							if (water->image)
							{
								destWater->image = builder->saveSubAsset(Game::XAssetType::ASSET_TYPE_IMAGE, water->image).image;
							}
						}
					}
					else if (textureDef->u.image)
					{
						destTextureDef->u.image = builder->saveSubAsset(Game::XAssetType::ASSET_TYPE_IMAGE, textureDef->u.image).image;
					}
				}

				Utils::Stream::ClearPointer(&dest->textureTable);
			}
		}

		if (asset->constantTable)
		{
			AssertSize(Game::MaterialConstantDef, 32);

			if (builder->hasPointer(asset->constantTable))
			{
				dest->constantTable = builder->getPointer(asset->constantTable);
			}
			else
			{
				buffer->align(Utils::Stream::ALIGN_16);
				builder->storePointer(asset->constantTable);

				buffer->saveArray(asset->constantTable, asset->constantCount);
				Utils::Stream::ClearPointer(&dest->constantTable);
			}
		}

		if (asset->stateBitsTable)
		{
			if (builder->hasPointer(asset->stateBitsTable))
			{
				dest->stateBitsTable = builder->getPointer(asset->stateBitsTable);
			}
			else
			{
				buffer->align(Utils::Stream::ALIGN_4);
				builder->storePointer(asset->stateBitsTable);

				buffer->save(asset->stateBitsTable, 8, asset->stateBitsCount);
				Utils::Stream::ClearPointer(&dest->stateBitsTable);
			}
		}

		buffer->popBlock();
	}
}
