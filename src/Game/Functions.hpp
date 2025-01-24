#pragma once

// Unsorted function definitions
namespace Game
{
	typedef void(*AngleVectors_t)(float* angles, float* forward, float* right, float* up);
	extern AngleVectors_t AngleVectors;

	typedef void(*Cbuf_AddServerText_f_t)();
	extern Cbuf_AddServerText_f_t Cbuf_AddServerText_f;

	typedef void(*Cbuf_AddText_t)(int localClientNum, const char* text);
	extern Cbuf_AddText_t Cbuf_AddText;

	typedef void(*Cbuf_InsertText_t)(int localClientNum, const char* text);
	extern Cbuf_InsertText_t Cbuf_InsertText;

	typedef void(*Cbuf_Execute_t)(int localClientNum, int controllerIndex);
	extern Cbuf_Execute_t Cbuf_Execute;

	typedef const char* (*CopyStringInternal_t)(const char* str);
	extern CopyStringInternal_t CopyStringInternal;

	typedef void(*CG_DrawDisconnect_t)(int localClientNum);
	extern CG_DrawDisconnect_t CG_DrawDisconnect;

	typedef void(*CG_LocationalTrace_t)(trace_t *results, const float *start, const float *end, int passEntityNum, int contentMask);
	extern  CG_LocationalTrace_t CG_LocationalTrace;

	typedef void(*CG_WorldTrace_t)(trace_t *results, const float *start, const float *end, Bounds *bounds, int brushmask);
	extern  CG_WorldTrace_t CG_WorldTrace;

	typedef void(*CG_NextWeapon_f_t)();
	extern CG_NextWeapon_f_t CG_NextWeapon_f;

	typedef int(*CG_GetClientNum_t)();
	extern CG_GetClientNum_t CG_GetClientNum;

	typedef void(*CG_PlayBoltedEffect_t)(int localClientNum, FxEffectDef* fxDef, int dobjHandle, unsigned int boneName);
	extern CG_PlayBoltedEffect_t CG_PlayBoltedEffect;

	typedef const DObj*(*CG_GetBoneIndex_t)(int localClientNum, unsigned int boneName, char* boneIndex);
	extern CG_GetBoneIndex_t CG_GetBoneIndex;

	typedef void(*CG_ScoresDown_f_t)();
	extern CG_ScoresDown_f_t CG_ScoresDown_f;

	typedef void(*CG_ScoresUp_f_t)();
	extern CG_ScoresUp_f_t CG_ScoresUp_f;

	typedef void(*CG_ScrollScoreboardUp_t)(cg_s* cgameGlob);
	extern CG_ScrollScoreboardUp_t CG_ScrollScoreboardUp;

	typedef void(*CG_ScrollScoreboardDown_t)(cg_s* cgameGlob);
	extern CG_ScrollScoreboardDown_t CG_ScrollScoreboardDown;

	typedef const char*(*CG_GetTeamName_t)(team_t team);
	extern CG_GetTeamName_t CG_GetTeamName;

	typedef void(*CG_SetupWeaponConfigString_t)(int localClientNum, unsigned int weapIndex);
	extern CG_SetupWeaponConfigString_t CG_SetupWeaponConfigString;

	typedef void(*Cmd_AddCommand_t)(const char* cmdName, void(*function), cmd_function_s* allocedCmd, int isKey);
	extern Cmd_AddCommand_t Cmd_AddCommand;

	typedef void(*Cmd_AddServerCommand_t)(const char* name, void(*callback), cmd_function_s* data);
	extern Cmd_AddServerCommand_t Cmd_AddServerCommand;

	typedef void(*Cmd_ExecuteSingleCommand_t)(int localClientNum, int controllerIndex, const char* cmd);
	extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

	typedef void(*Cmd_ForEach_t)(void(*callback)(const char* str));
	extern Cmd_ForEach_t Cmd_ForEach;

	typedef char*(*Con_DrawMiniConsole_t)(int localClientNum, int xPos, int yPos, float alpha);
	extern Con_DrawMiniConsole_t Con_DrawMiniConsole;

	typedef void (*Con_DrawSolidConsole_t)();
	extern Con_DrawSolidConsole_t Con_DrawSolidConsole;

	typedef bool(*Con_CancelAutoComplete_t)();
	extern Con_CancelAutoComplete_t Con_CancelAutoComplete;

	typedef bool(*Con_IsDvarCommand_t)(const char* cmd);
	extern Con_IsDvarCommand_t Con_IsDvarCommand;

	typedef bool(*Encode_Init_t)(const char* );
	extern Encode_Init_t Encode_Init;

	typedef void(*Field_Clear_t)(void* field);
	extern Field_Clear_t Field_Clear;

	typedef void(*FreeMemory_t)(void* buffer);
	extern FreeMemory_t FreeMemory;

	typedef void(*Free_String_t)(const char* string);
	extern Free_String_t Free_String;

	typedef void(*Svcmd_EntityList_f_t)();
	extern Svcmd_EntityList_f_t Svcmd_EntityList_f;

	typedef int(*Reader_t)(char const*, int *);

	typedef bool(*Image_LoadFromFileWithReader_t)(GfxImage* image, Reader_t reader);
	extern Image_LoadFromFileWithReader_t Image_LoadFromFileWithReader;

	typedef void(*Image_Release_t)(GfxImage* image);
	extern Image_Release_t Image_Release;

	typedef char*(*Info_ValueForKey_t)(const char* s, const char* key);
	extern Info_ValueForKey_t Info_ValueForKey;

	typedef int(*Info_Validate_t)(const char* s);
	extern Info_Validate_t Info_Validate;

	typedef void(*Key_SetCatcher_t)(int localClientNum, int catcher);
	extern Key_SetCatcher_t Key_SetCatcher;

	typedef void(*Key_RemoveCatcher_t)(int localClientNum, int andMask);
	extern Key_RemoveCatcher_t Key_RemoveCatcher;

	typedef bool(*Key_IsCatcherActive_t)(int localClientNum, int mask);
	extern Key_IsCatcherActive_t Key_IsCatcherActive;

	typedef void(*Key_SetBinding_t)(int localClientNum, int keynum, const char* binding);
	extern Key_SetBinding_t Key_SetBinding;

	typedef void(*LargeLocalInit_t)();
	extern LargeLocalInit_t LargeLocalInit;

	typedef bool(*Load_Stream_t)(bool atStreamStart, const void* ptr, unsigned int size);
	extern Load_Stream_t Load_Stream;

	typedef void(*Load_XString_t)(bool atStreamStart);
	extern Load_XString_t Load_XString;

	typedef void(*Load_XModelPtr_t)(bool atStreamStart);
	extern Load_XModelPtr_t Load_XModelPtr;

	typedef void(*Load_XModelSurfsFixup_t)(XModelSurfs**, XModelLodInfo*);
	extern Load_XModelSurfsFixup_t Load_XModelSurfsFixup;

	typedef void(*Load_XStringArray_t)(bool atStreamStart, int count);
	extern Load_XStringArray_t Load_XStringArray;

	typedef void(*Load_XStringCustom_t)(const char** str);
	extern Load_XStringCustom_t Load_XStringCustom;

	typedef void(*Load_FxEffectDefHandle_t)(bool atStreamStart);
	extern Load_FxEffectDefHandle_t Load_FxEffectDefHandle;

	typedef void(*Load_FxElemDef_t)(bool atStreamStart);
	extern Load_FxElemDef_t Load_FxElemDef;

	typedef void(*Load_GfxImagePtr_t)(bool atStreamStart);
	extern Load_GfxImagePtr_t Load_GfxImagePtr;

	typedef void(*Load_GfxTextureLoad_t)(bool atStreamStart);
	extern Load_GfxTextureLoad_t Load_GfxTextureLoad;

	typedef int(*Load_Texture_t)(GfxImageLoadDef** loadDef, GfxImage* image);
	extern Load_Texture_t Load_Texture;

	typedef void(*Load_SndAliasCustom_t)(snd_alias_list_t** var);
	extern Load_SndAliasCustom_t Load_SndAliasCustom;

	typedef void(*Load_MaterialHandle_t)(bool atStreamStart);
	extern Load_MaterialHandle_t Load_MaterialHandle;

	typedef void(*Load_PhysCollmapPtr_t)(bool atStreamStart);
	extern Load_PhysCollmapPtr_t Load_PhysCollmapPtr;

	typedef void(*Load_PhysPresetPtr_t)(bool atStreamStart);
	extern Load_PhysPresetPtr_t Load_PhysPresetPtr;

	typedef void(*Load_TracerDefPtr_t)(bool atStreamStart);
	extern Load_TracerDefPtr_t Load_TracerDefPtr;

	typedef void(*Load_snd_alias_list_nameArray_t)(bool atStreamStart, int count);
	extern Load_snd_alias_list_nameArray_t Load_snd_alias_list_nameArray;

	typedef void(*Menus_CloseAll_t)(UiContext* dc);
	extern Menus_CloseAll_t Menus_CloseAll;

	typedef void(*Menus_CloseRequest_t)(UiContext* dc, menuDef_t* menu);
	extern Menus_CloseRequest_t Menus_CloseRequest;

	typedef int(*Menus_OpenByName_t)(UiContext* dc, const char* p);
	extern Menus_OpenByName_t Menus_OpenByName;

	typedef menuDef_t*(*Menus_FindByName_t)(UiContext* dc, const char* name);
	extern Menus_FindByName_t Menus_FindByName;

	typedef bool(*Menu_IsVisible_t)(UiContext* dc, menuDef_t* menu);
	extern Menu_IsVisible_t Menu_IsVisible;

	typedef bool(*Menus_MenuIsInStack_t)(UiContext* dc, menuDef_t* menu);
	extern Menus_MenuIsInStack_t Menus_MenuIsInStack;

	typedef void(*Menu_HandleKey_t)(UiContext* ctx, menuDef_t* menu, Game::keyNum_t key, int down);
	extern Menu_HandleKey_t Menu_HandleKey;

	typedef menuDef_t*(*Menu_GetFocused_t)(UiContext* ctx);
	extern Menu_GetFocused_t Menu_GetFocused;

	typedef void(*Menu_Setup_t)(UiContext* dc);
	extern Menu_Setup_t Menu_Setup;

	typedef bool(*UI_KeyEvent_t)(int clientNum, int key, int down);
	extern UI_KeyEvent_t UI_KeyEvent;

	typedef const char*(*UI_SafeTranslateString_t)(const char* reference);
	extern UI_SafeTranslateString_t UI_SafeTranslateString;

	typedef void(*UI_ReplaceConversions_t)(const char* sourceString, ConversionArguments* arguments, char* outputString, size_t outputStringSize);
	extern UI_ReplaceConversions_t UI_ReplaceConversions;

	typedef int(*UI_ParseInfos_t)(const char* buf, int max, char** infos);
	extern UI_ParseInfos_t UI_ParseInfos;

	typedef const char*(*UI_GetMapDisplayName_t)(const char* pszMap);
	extern UI_GetMapDisplayName_t UI_GetMapDisplayName;

	typedef const char* (*UI_GetGameTypeDisplayName_t)(const char* pszGameType);
	extern UI_GetGameTypeDisplayName_t UI_GetGameTypeDisplayName;

	typedef int(*ParseConfigStringToStruct_t)(void* pStruct, const Game::cspField_t* pFieldList, const int iNumFields, const char* pszBuffer, const int iMaxFieldTypes, int(__cdecl* parseSpecialFieldType)(char*, const char*, const int), void(__cdecl* parseStrcpy)(char*, char*));
	extern ParseConfigStringToStruct_t ParseConfigStringToStruct;

	typedef void(*MSG_Init_t)(msg_t* buf, unsigned char* data, int length);
	extern MSG_Init_t MSG_Init;

	typedef void(*MSG_ReadData_t)(msg_t* msg, void* data, int len);
	extern MSG_ReadData_t MSG_ReadData;

	typedef int(*MSG_ReadLong_t)(msg_t* msg);
	extern MSG_ReadLong_t MSG_ReadLong;

	typedef int(*MSG_ReadBit_t)(msg_t* msg);
	extern MSG_ReadBit_t MSG_ReadBit;

	typedef int(*MSG_ReadBits_t)(msg_t* msg, int bits);
	extern MSG_ReadBits_t MSG_ReadBits;

	typedef int(*MSG_ReadShort_t)(msg_t* msg);
	extern MSG_ReadShort_t MSG_ReadShort;

	typedef __int64(*MSG_ReadInt64_t)(msg_t* msg);
	extern MSG_ReadInt64_t MSG_ReadInt64;

	typedef char*(*MSG_ReadBigString_t)(msg_t* msg);
	extern MSG_ReadBigString_t MSG_ReadBigString;

	typedef char*(*MSG_ReadStringLine_t)(msg_t *msg, char *string, unsigned int maxChars);
	extern MSG_ReadStringLine_t MSG_ReadStringLine;

	typedef void(*MSG_WriteByte_t)(msg_t* msg, int c);
	extern MSG_WriteByte_t MSG_WriteByte;

	typedef void(*MSG_WriteData_t)(msg_t *buf, const void *data, int length);
	extern MSG_WriteData_t MSG_WriteData;

	typedef void(*MSG_WriteLong_t)(msg_t *msg, int c);
	extern MSG_WriteLong_t MSG_WriteLong;

	typedef void(*MSG_WriteShort_t)(msg_t* msg, int s);
	extern MSG_WriteShort_t MSG_WriteShort;

	typedef void(*MSG_WriteString_t)(msg_t* msg, const char *str);
	extern MSG_WriteString_t MSG_WriteString;

	typedef void(*MSG_Discard_t)(msg_t* msg);
	extern MSG_Discard_t MSG_Discard;

	typedef int(*MSG_ReadByte_t)(msg_t* msg);
	extern MSG_ReadByte_t MSG_ReadByte;

	typedef bool(*MSG_ReadDeltaUsercmdKey_t)(msg_t* msg, int key, const usercmd_s* from, usercmd_s* to);
	extern MSG_ReadDeltaUsercmdKey_t MSG_ReadDeltaUsercmdKey;

	typedef int(*MSG_ReadBitsCompress_t)(const unsigned char* from, unsigned char* to, int size);
	extern MSG_ReadBitsCompress_t MSG_ReadBitsCompress;

	typedef int(*MSG_WriteBitsCompress_t)(bool trainHuffman, const unsigned char* from, unsigned char* to, int size);
	extern MSG_WriteBitsCompress_t MSG_WriteBitsCompress;

	typedef void(*Huff_offsetReceive_t)(nodetype* node, int* ch, const unsigned char* fin, int* offset);
	extern Huff_offsetReceive_t Huff_offsetReceive;

	typedef void(*NetadrToSockadr_t)(netadr_t *a, sockaddr *s);
	extern NetadrToSockadr_t NetadrToSockadr;

	typedef const char*(*NET_AdrToString_t)(netadr_t adr);
	extern NET_AdrToString_t NET_AdrToString;

	typedef bool(*NET_CompareAdr_t)(netadr_t a, netadr_t b);
	extern NET_CompareAdr_t NET_CompareAdr;

	typedef int(*NET_CompareBaseAdr_t)(netadr_t a, netadr_t b);
	extern NET_CompareBaseAdr_t NET_CompareBaseAdr;

	typedef void(*NET_DeferPacketToClient_t)(netadr_t*, msg_t*);
	extern NET_DeferPacketToClient_t NET_DeferPacketToClient;

	typedef const char* (*NET_ErrorString_t)();
	extern NET_ErrorString_t NET_ErrorString;

	typedef void(*NET_Init_t)();
	extern NET_Init_t NET_Init;

	typedef bool(*NET_IsLocalAddress_t)(netadr_t adr);
	extern NET_IsLocalAddress_t NET_IsLocalAddress;

	typedef int(*NET_StringToAdr_t)(const char* s, netadr_t* a);
	extern NET_StringToAdr_t NET_StringToAdr;

	typedef void(*NET_OutOfBandPrint_t)(netsrc_t sock, netadr_t adr, const char* data);
	extern NET_OutOfBandPrint_t NET_OutOfBandPrint;

	typedef void(*NET_OutOfBandData_t)(netsrc_t sock, netadr_t adr, const char* format, int len);
	extern NET_OutOfBandData_t NET_OutOfBandData;

	typedef int(*NET_OutOfBandVoiceData_t)(netsrc_t sock, netadr_t adr, unsigned char* format, int len, bool voiceData);
	extern NET_OutOfBandVoiceData_t NET_OutOfBandVoiceData;

	typedef void(*Live_MPAcceptInvite_t)(_XSESSION_INFO *hostInfo, int controllerIndex, bool fromGameInvite);
	extern Live_MPAcceptInvite_t Live_MPAcceptInvite;

	typedef int(*Live_GetMapIndex_t)(const char* mapname);
	extern Live_GetMapIndex_t Live_GetMapIndex;

	typedef int(*Live_GetPrestige_t)(int controllerIndex);
	extern Live_GetPrestige_t Live_GetPrestige;

	typedef int(*Live_GetXp_t)(int controllerIndex);
	extern Live_GetXp_t Live_GetXp;

	typedef const char*(*Live_GetLocalClientName_t)(int controllerIndex);
	extern Live_GetLocalClientName_t Live_GetLocalClientName;

	typedef bool(*Live_IsSystemUiActive_t)();
	extern Live_IsSystemUiActive_t Live_IsSystemUiActive;

	typedef int(*LiveStorage_GetStat_t)(int controllerIndex, int index);
	extern LiveStorage_GetStat_t LiveStorage_GetStat;

	typedef void(*LiveStorage_SetStat_t)(int controllerIndex, int index, int value);
	extern LiveStorage_SetStat_t LiveStorage_SetStat;

	typedef char*(*Scr_AddSourceBuffer_t)(const char* filename, const char* extFilename, const char* codePos, bool archive);
	extern Scr_AddSourceBuffer_t Scr_AddSourceBuffer;

	typedef int(*Party_GetMaxPlayers_t)(PartyData* party);
	extern Party_GetMaxPlayers_t Party_GetMaxPlayers;

	typedef int(*PartyHost_CountMembers_t)(PartyData* party);
	extern PartyHost_CountMembers_t PartyHost_CountMembers;

	typedef netadr_t *(*PartyHost_GetMemberAddressBySlot_t)(int unk, void *party, const int slot);
	extern PartyHost_GetMemberAddressBySlot_t PartyHost_GetMemberAddressBySlot;

	typedef const char *(*PartyHost_GetMemberName_t)(PartyData* party, const int clientNum);
	extern PartyHost_GetMemberName_t PartyHost_GetMemberName;

	typedef int(*Party_InParty_t)(PartyData* party);
	extern Party_InParty_t Party_InParty;

	typedef void(*Playlist_ParsePlaylists_t)(const char* data);
	extern Playlist_ParsePlaylists_t Playlist_ParsePlaylists;

	typedef Font_s*(*R_RegisterFont_t)(const char* asset, int safe);
	extern R_RegisterFont_t R_RegisterFont;

	typedef void(*R_AddCmdDrawText_t)(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style);
	extern R_AddCmdDrawText_t R_AddCmdDrawText;

	typedef void(*R_AddCmdDrawStretchPic_t)(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, const float *color, Game::Material* material);
	extern R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic;

	typedef void*(*R_AllocStaticIndexBuffer_t)(IDirect3DIndexBuffer9** store, int length);
	extern R_AllocStaticIndexBuffer_t R_AllocStaticIndexBuffer;

	typedef bool(*R_Cinematic_StartPlayback_Now_t)();
	extern R_Cinematic_StartPlayback_Now_t R_Cinematic_StartPlayback_Now;

	typedef void(*R_LoadGraphicsAssets_t)();
	extern R_LoadGraphicsAssets_t R_LoadGraphicsAssets;

	typedef int(*R_TextWidth_t)(const char* text, int maxlength, Font_s* font);
	extern R_TextWidth_t R_TextWidth;

	typedef int(*R_TextHeight_t)(Font_s* font);
	extern R_TextHeight_t R_TextHeight;

	typedef void(*R_FlushSun_t)();
	extern R_FlushSun_t R_FlushSun;

	typedef GfxWorld*(*R_SortWorldSurfaces_t)();
	extern R_SortWorldSurfaces_t R_SortWorldSurfaces;

	typedef void* (*GetMemory_t)(unsigned int size);
	extern GetMemory_t GetMemory;

	typedef void*(*GetClearedMemory_t)(unsigned int size);
	extern GetClearedMemory_t GetClearedMemory;

	typedef void(*PS_CreatePunctuationTable_t)(script_s* script, punctuation_s* punctuations);
	extern PS_CreatePunctuationTable_t PS_CreatePunctuationTable;

	typedef void(*free_expression_t)(Statement_s* statement);
	extern free_expression_t free_expression;

	typedef char*(*SE_Load_t)(const char* psFileName, bool forceEnglish);
	extern SE_Load_t SE_Load;

	typedef char*(*SEH_StringEd_GetString_t)(const char* string);
	extern SEH_StringEd_GetString_t SEH_StringEd_GetString;

	typedef unsigned int(*SEH_ReadCharFromString_t)(const char** text, int* isTrailingPunctuation);
	extern SEH_ReadCharFromString_t SEH_ReadCharFromString;

	typedef int(*SEH_GetCurrentLanguage_t)();
	extern SEH_GetCurrentLanguage_t SEH_GetCurrentLanguage;

	typedef void(*SND_Init_t)(int a1, int a2, int a3);
	extern SND_Init_t SND_Init;

	typedef void(*SND_InitDriver_t)();
	extern SND_InitDriver_t SND_InitDriver;

	typedef void(*SockadrToNetadr_t)(sockaddr *s, netadr_t *a);
	extern SockadrToNetadr_t SockadrToNetadr;

	typedef void(*Steam_JoinLobby_t)(SteamID, char);
	extern Steam_JoinLobby_t Steam_JoinLobby;

	typedef void(*TeleportPlayer_t)(gentity_s* entity, float* pos, float* orientation);
	extern TeleportPlayer_t TeleportPlayer;

	typedef void(*UI_AddMenuList_t)(UiContext* dc, MenuList* menuList, int close);
	extern UI_AddMenuList_t UI_AddMenuList;

	typedef uiMenuCommand_t(*UI_GetActiveMenu_t)(int localClientNum);
	extern UI_GetActiveMenu_t UI_GetActiveMenu;

	typedef char*(*UI_CheckStringTranslation_t)(char*, char*);
	extern UI_CheckStringTranslation_t UI_CheckStringTranslation;

	typedef MenuList*(*UI_LoadMenus_t)(const char* menuFile, int imageTrack);
	extern UI_LoadMenus_t UI_LoadMenus;

	typedef void(*UI_UpdateArenas_t)();
	extern UI_UpdateArenas_t UI_UpdateArenas;

	typedef void(*UI_SortArenas_t)();
	extern UI_SortArenas_t UI_SortArenas;

	typedef void(*UI_DrawHandlePic_t)(ScreenPlacement* scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, const float* color, Material* material);
	extern UI_DrawHandlePic_t UI_DrawHandlePic;

	typedef ScreenPlacement*(*ScrPlace_GetActivePlacement_t)(int localClientNum);
	extern ScrPlace_GetActivePlacement_t ScrPlace_GetActivePlacement;

	typedef int(*UI_TextWidth_t)(const char* text, int maxChars, Font_s* font, float scale);
	extern UI_TextWidth_t UI_TextWidth;

	typedef int(*UI_TextHeight_t)(Font_s* font, float scale);
	extern UI_TextHeight_t UI_TextHeight;

	typedef void(*UI_DrawText_t)(const ScreenPlacement* scrPlace, const char* text, int maxChars, Font_s* font, float x, float y, int horzAlign, int vertAlign, float scale, const float* color, int style);
	extern UI_DrawText_t UI_DrawText;

	typedef Font_s*(*UI_GetFontHandle_t)(ScreenPlacement* scrPlace, int fontEnum, float scale);
	extern UI_GetFontHandle_t UI_GetFontHandle;

	typedef void(*ScrPlace_ApplyRect_t)(const ScreenPlacement* scrPlace, float* x, float* y, float* w, float* h, int horzAlign, int vertAlign);
	extern ScrPlace_ApplyRect_t ScrPlace_ApplyRect;

	typedef const char*(*Win_GetLanguage_t)();
	extern Win_GetLanguage_t Win_GetLanguage;

	typedef void(*Vec3UnpackUnitVec_t)(PackedUnitVec, vec3_t*);
	extern Vec3UnpackUnitVec_t Vec3UnpackUnitVec;

	typedef float(*vectoryaw_t)(vec2_t* vec);
	extern vectoryaw_t vectoryaw;

	typedef float(*AngleNormalize360_t)(float val);
	extern AngleNormalize360_t AngleNormalize360;

	typedef void(*_VectorMA_t)(float* va, float scale, float* vb, float* vc);
	extern _VectorMA_t _VectorMA;

	typedef void(*unzClose_t)(void* handle);
	extern unzClose_t unzClose;

	typedef void(*RB_DrawCursor_t)(Material* material, char cursor, float x, float y, float sinAngle, float cosAngle, Font_s* font, float xScale, float yScale, unsigned int color);
	extern RB_DrawCursor_t RB_DrawCursor;

	typedef float(*R_NormalizedTextScale_t)(Font_s* font, float scale);
	extern R_NormalizedTextScale_t R_NormalizedTextScale;

	typedef void(*Material_Process2DTextureCoordsForAtlasing_t)(const Material* material, float* s0, float* s1, float* t0, float* t1);
	extern Material_Process2DTextureCoordsForAtlasing_t Material_Process2DTextureCoordsForAtlasing;

	typedef void(*Byte4PackRgba_t)(const float* from, char* to);
	extern Byte4PackRgba_t Byte4PackRgba;

	typedef int(*RandWithSeed_t)(int* seed);
	extern RandWithSeed_t RandWithSeed;

	typedef void(*GetDecayingLetterInfo_t)(unsigned int letter, int* randSeed, int decayTimeElapsed, int fxBirthTime, int fxDecayDuration, unsigned __int8 alpha, bool* resultSkipDrawing, char* resultAlpha, unsigned int* resultLetter, bool* resultDrawExtraFxChar);
	extern GetDecayingLetterInfo_t GetDecayingLetterInfo;

	typedef void(*Field_Draw_t)(int localClientNum, field_t* edit, int x, int y, int horzAlign, int vertAlign);
	extern Field_Draw_t Field_Draw;

	typedef void(*Field_AdjustScroll_t)(ScreenPlacement* scrPlace, field_t* edit);
	extern Field_AdjustScroll_t Field_AdjustScroll;

	typedef void(*AimAssist_ApplyAutoMelee_t)(const AimInput* input, AimOutput* output);
	extern AimAssist_ApplyAutoMelee_t AimAssist_ApplyAutoMelee;

	typedef gentity_s*(*Weapon_RocketLauncher_Fire_t)(gentity_s* ent, unsigned int weaponIndex, float spread, weaponParms* wp, const float* gunVel, lockonFireParms* lockParms, bool magicBullet);
	extern Weapon_RocketLauncher_Fire_t Weapon_RocketLauncher_Fire;

	typedef int(*Bullet_Fire_t)(gentity_s* attacker, float spread, weaponParms* wp, gentity_s* weaponEnt, PlayerHandIndex hand, int gameTime);
	extern Bullet_Fire_t Bullet_Fire;

	typedef BOOL(*IN_RecenterMouse_t)();
	extern IN_RecenterMouse_t IN_RecenterMouse;

	typedef void(*IN_MouseMove_t)();
	extern IN_MouseMove_t IN_MouseMove;

	typedef void(*IN_MouseEvent_t)(int flags);
	extern IN_MouseEvent_t IN_MouseEvent;

	typedef void(*IN_Frame_t)();
	extern IN_Frame_t IN_Frame;

	typedef void(*IN_Init_t)();
	extern IN_Init_t IN_Init;

	typedef void(*IN_Shutdown_t)();
	extern IN_Shutdown_t IN_Shutdown;

	typedef void(*Touch_Item_t)(gentity_s* ent, gentity_s* other, int touched);
	extern Touch_Item_t Touch_Item;

	typedef void(*Add_Ammo_t)(gentity_s* ent, unsigned int weaponIndex, unsigned char weaponModel, int count, int fillClip);
	extern Add_Ammo_t Add_Ammo;

	typedef void(*ClientUserinfoChanged_t)(int clientNum);
	extern ClientUserinfoChanged_t ClientUserinfoChanged;

	typedef void(*player_die_t)(gentity_s* self, const gentity_s* inflictor, gentity_s* attacker, int damage, int meansOfDeath, int iWeapon, const float* vDir, const hitLocation_t hitLoc, int psTimeOffset);
	extern player_die_t player_die;

	typedef float(*Vec3Normalize_t)(float* v);
	extern Vec3Normalize_t Vec3Normalize;

	typedef void(*Vec3NormalizeFast_t)(float* v);
	extern Vec3NormalizeFast_t Vec3NormalizeFast;

	typedef float(*Vec2Normalize_t)(float* v);
	extern Vec2Normalize_t Vec2Normalize;

	typedef void(*Vec2NormalizeFast_t)(float* v);
	extern Vec2NormalizeFast_t Vec2NormalizeFast;

	typedef void(*I_strncpyz_t)(char* dest, const char* src, int destsize);
	extern I_strncpyz_t I_strncpyz;

	typedef char*(*I_CleanStr_t)(char* string);
	extern I_CleanStr_t I_CleanStr;

	typedef bool(*I_isdigit_t)(int c);
	extern I_isdigit_t I_isdigit;

	typedef void(*XNAddrToString_t)(const XNADDR* xnaddr, char* str);
	extern XNAddrToString_t XNAddrToString;

	typedef int(*Voice_IncomingVoiceData_t)(const SessionData* session, int clientNum, unsigned char* data, int size);
	extern Voice_IncomingVoiceData_t Voice_IncomingVoiceData;

	typedef bool(*Voice_IsClientTalking_t)(int clientNum);
	extern Voice_IsClientTalking_t Voice_IsClientTalking;

	typedef int(*LargeLocalBegin_t)(int size);
	extern LargeLocalBegin_t LargeLocalBegin;

	typedef int(*LargeLocalBeginRight_t)(int size);
	extern LargeLocalBeginRight_t LargeLocalBeginRight;

	typedef void(*LargeLocalReset_t)();
	extern LargeLocalReset_t LargeLocalReset;

	typedef StructuredDataDef*(*StructuredDataDef_GetAsset_t)(const char* filename, unsigned int maxSize);
	extern StructuredDataDef_GetAsset_t StructuredDataDef_GetAsset;

	typedef void(*StringTable_GetAsset_FastFile_t)(const char* filename, const StringTable** tablePtr);
	extern StringTable_GetAsset_FastFile_t StringTable_GetAsset_FastFile;

	typedef const char*(*StringTable_Lookup_t)(const StringTable* table, const int comparisonColumn, const char* value, const int valueColumn);
	extern StringTable_Lookup_t StringTable_Lookup;

	typedef int(*StringTable_HashString_t)(const char* string);
	extern StringTable_HashString_t StringTable_HashString;

	typedef int(*StringTable_LookupRowNumForValue_t)(const StringTable* table, int comparisonColumn, const char* value);
	extern StringTable_LookupRowNumForValue_t StringTable_LookupRowNumForValue;

	typedef const char*(*StringTable_GetColumnValueForRow_t)(const StringTable*, int row, int column);
	extern StringTable_GetColumnValueForRow_t StringTable_GetColumnValueForRow;

	typedef void(*longjmp_internal_t)(jmp_buf env, int status);
	extern longjmp_internal_t longjmp_internal;

	constexpr std::size_t STATIC_MAX_LOCAL_CLIENTS = 1;
	constexpr std::size_t MAX_LOCAL_CLIENTS = 1;
	constexpr std::size_t MAX_CLIENTS = 18;

	constexpr auto MAX_CMD_BUFFER = 0x10000;
	constexpr auto MAX_CMD_LINE = 0x1000;
	constexpr auto CMD_MAX_NESTING = 8;
	extern CmdArgs* cmd_args;
	extern CmdArgs* sv_cmd_args;

	extern cmd_function_s** cmd_functions;

	extern float* cgameFOVSensitivityScale;

	extern source_s** sourceFiles;

	extern UiContext* uiContext;
	extern UiContext* cgDC;
	extern const ExpressionSupportingData* menuSupportingData;

	extern int* arenaCount;
	extern mapArena_t* arenas;

	extern int* gameTypeCount;
	extern gameTypeName_t* gameTypes;

	extern bool* g_lobbyCreateInProgress;
	extern PartyData* g_lobbyData;
	extern PartyData* g_partyData;

	extern SessionData* g_serverSession;

	extern int* numIP;
	extern netIP_t* localIP;

	extern netadr_t* connectedHost;
	extern SOCKET* ip_socket;

	extern SafeArea* safeArea;

	extern SpawnVar* spawnVars;
	extern MapEnts** marMapEntsPtr;

	extern IDirect3D9** d3d9;
	extern IDirect3DDevice9** dx_ptr;

	extern mapname_t* mapnames;

	extern char*** varXString;
	extern TracerDef*** varTracerDefPtr;
	extern XModel*** varXModelPtr;
	extern XModel** varXModel;
	extern PathData** varPathData;
	extern const char** varConstChar;
	extern Material*** varMaterialHandle;
	extern FxEffectDef*** varFxEffectDefHandle;
	extern PhysCollmap*** varPhysCollmapPtr;
	extern PhysPreset*** varPhysPresetPtr;
	extern MaterialPass** varMaterialPass;
	extern snd_alias_list_t*** varsnd_alias_list_name;
	extern MaterialVertexShader** varMaterialVertexShader;

	extern FxElemField* s_elemFields;

	extern visField_t* visionDefFields;

	extern infoParm_t* infoParams;

	extern GfxScene* scene;

	extern Console* con;
	extern ConDrawInputGlob* conDrawInputGlob;

	extern int* g_console_field_width;
	extern float* g_console_char_height;
	extern field_t* g_consoleField;

	extern sharedUiInfo_t* sharedUiInfo;
	extern ScreenPlacement* scrPlaceFull;
	extern ScreenPlacement* scrPlaceFullUnsafe;
	extern ScreenPlacement* scrPlaceView;

	extern cg_s* cgArray;
	extern cgs_t* cgsArray;

	extern PlayerKeyState* playerKeys;
	extern kbutton_t* playersKb;
	extern AimAssistGlobals* aaGlobArray;

	constexpr auto KEY_NAME_COUNT = 95;
	constexpr auto LOCALIZED_KEY_NAME_COUNT = 95;
	extern keyname_t* keyNames;
	extern keyname_t* localizedKeyNames;

	constexpr auto AIM_ASSIST_GRAPH_COUNT = 4u;
	extern GraphFloat* aaInputGraph;

	extern const char* MY_CMDS;

	constexpr auto MAX_MODELS = 512;
	extern XModel** cached_models;

	extern float (*CorrectSolidDeltas)[26][3];

	extern level_locals_t* level;

	extern float (*penetrationDepthTable)[PENETRATE_TYPE_COUNT][SURF_TYPE_COUNT];

	extern char (*com_consoleLines)[32];

	extern WinMouseVars_t* s_wmv;

	extern int* window_center_x;
	extern int* window_center_y;

	extern DeferredQueue* deferredQueue;

	extern int* g_waitingForKey;

	extern Material** whiteMaterial;

	extern unsigned long* g_dwTlsIndex;

	extern bgs_t* level_bgs;

	constexpr std::size_t PLAYER_CARD_UI_STRING_COUNT = 18;
	extern unsigned int* playerCardUIStringIndex;
	extern char (*playerCardUIStringBuf)[PLAYER_CARD_UI_STRING_COUNT][38];

	extern uiInfo_s* uiInfoArray;

	extern int* logfile;

	extern GamerSettingState* gamerSettings;

	extern unsigned char* g_largeLocalBuf;
	extern int* g_largeLocalPos;
	extern int* g_largeLocalRightPos;

	extern char** ui_arenaInfos;
	extern int* ui_numArenas;
	extern int* ui_arenaBufPos;

	extern punctuation_s* default_punctuations;
	extern int* numtokens;

	extern bool* s_havePlaylists;

	extern huffman_t* msgHuff;

	constexpr auto MAX_MSGLEN = 0x20000;

	ScreenPlacement* ScrPlace_GetFullPlacement();
	ScreenPlacement* ScrPlace_GetUnsafeFullPlacement();

	void UI_FilterStringForButtonAnimation(char* str, unsigned int strMaxSize);

	void Menu_FreeItem(itemDef_s* item);
	void Menu_SetNextCursorItem(UiContext* ctx, menuDef_t* currentMenu, int unk = 1);
	void Menu_SetPrevCursorItem(UiContext* ctx, menuDef_t* currentMenu, int unk = 1);
	const char* TableLookup(StringTable* stringtable, int row, int column);
	const char* UI_LocalizeGameType(const char* gameType);
	float UI_GetScoreboardLeft(void*);

	bool PM_IsAdsAllowed(playerState_s* ps);

	void ShowMessageBox(const std::string& message, const std::string& title);

	unsigned int R_HashString(const char* string);
	unsigned int R_HashString(const char* string, size_t maxLen);
	void R_LoadSunThroughDvars(const char* mapname, sunflare_t* sun);
	void R_SetSunFromDvars(sunflare_t* sun);

	void IN_KeyUp(kbutton_t* button);
	void IN_KeyDown(kbutton_t* button);

	void Load_IndexBuffer(void* data, IDirect3DIndexBuffer9** storeHere, int count);
	void Load_VertexBuffer(void* data, IDirect3DVertexBuffer9** where, int len);

	void Image_Setup(GfxImage* image, unsigned int width, unsigned int height, unsigned int depth, unsigned int flags, _D3DFORMAT format);

	void Vec2UnpackTexCoords(const PackedTexCoords in, vec2_t* out);
	void MatrixVecMultiply(const float(&mulMat)[3][3], const vec3_t& mulVec, vec3_t& solution);
	void QuatRot(vec3_t* vec, const vec4_t* quat);
	void QuatMultiply(const vec4_t* q1, const vec4_t* q2, vec4_t* res);

	void SortWorldSurfaces(GfxWorld* world);
	void R_AddDebugLine(float* color, float* v1, float* v2);
	void R_AddDebugString(float *color, float *pos, float scale, const char *str);
	void R_AddDebugBounds(float* color, Bounds* b);
	void R_AddDebugBounds(float* color, Bounds* b, const float(*quat)[4]);

	Glyph* R_GetCharacterGlyph(Font_s* font, unsigned int letter);
	bool SetupPulseFXVars(const char* text, int maxLength, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration, bool* resultDrawRandChar, int* resultRandSeed, int* resultMaxLength, bool* resultDecaying, int* resultDecayTimeElapsed);
	void RB_DrawChar(Material* material, float x, float y, float w, float h, float sinAngle, float cosAngle, Glyph* glyph, unsigned int color);
	void RB_DrawStretchPicRotate(Material* material, float x, float y, float w, float h, float s0, float t0, float s1, float t1, float sinAngle, float cosAngle, unsigned int color);
	char ModulateByteColors(char colorA, char colorB);

	float GraphGetValueFromFraction(int knotCount, const float(*knots)[2], float fraction);
	float GraphFloat_GetValue(const GraphFloat* graph, const float fraction);

	void AimAssist_UpdateTweakables(int localClientNum);
	void AimAssist_UpdateAdsLerp(const AimInput* input);

	bool ApplyTokenToField(unsigned int fieldNum, const char* token, visionSetVars_t* settings);

	int SEH_GetLocalizedTokenReference(char* token, const char* reference, const char* messageType, msgLocErrType_t errType);

	void I_strncpyz_s(char* dest, std::size_t destsize, const char* src, std::size_t count);
	void I_strcpy(char* dest, std::size_t destsize, const char* src);

	void Player_SwitchToWeapon(gentity_s* player);
}
