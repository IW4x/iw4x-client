#include <STDInclude.hpp>

// Unsorted function definitions
namespace Game
{
	AngleVectors_t AngleVectors = AngleVectors_t(0x4691A0);

	Cbuf_AddServerText_f_t Cbuf_AddServerText_f = Cbuf_AddServerText_f_t(0x4BB9B0);
	Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x404B20);
	Cbuf_InsertText_t Cbuf_InsertText = Cbuf_InsertText_t(0x4940B0);
	Cbuf_Execute_t Cbuf_Execute = Cbuf_Execute_t(0x4E2C80);

	CopyStringInternal_t CopyStringInternal = CopyStringInternal_t(0x4F3C80);

	CG_LocationalTrace_t CG_LocationalTrace = CG_LocationalTrace_t(0x48B1D0);
	CG_WorldTrace_t CG_WorldTrace = CG_WorldTrace_t(0x501F00);
	CG_DrawDisconnect_t CG_DrawDisconnect = CG_DrawDisconnect_t(0x454A70);
	CG_NextWeapon_f_t CG_NextWeapon_f = CG_NextWeapon_f_t(0x449DE0);
	CG_GetClientNum_t CG_GetClientNum = CG_GetClientNum_t(0x433700);
	CG_PlayBoltedEffect_t CG_PlayBoltedEffect = CG_PlayBoltedEffect_t(0x430E10);
	CG_GetBoneIndex_t CG_GetBoneIndex = CG_GetBoneIndex_t(0x504F20);
	CG_ScoresDown_f_t CG_ScoresDown_f = CG_ScoresDown_f_t(0x580370);
	CG_ScoresUp_f_t CG_ScoresUp_f = CG_ScoresUp_f_t(0x5802C0);
	CG_ScrollScoreboardUp_t CG_ScrollScoreboardUp = CG_ScrollScoreboardUp_t(0x47A5C0);
	CG_ScrollScoreboardDown_t CG_ScrollScoreboardDown = CG_ScrollScoreboardDown_t(0x493B50);
	CG_GetTeamName_t CG_GetTeamName = CG_GetTeamName_t(0x4B6210);
	CG_SetupWeaponConfigString_t CG_SetupWeaponConfigString = CG_SetupWeaponConfigString_t(0x4BD520);

	Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x470090);
	Cmd_AddServerCommand_t Cmd_AddServerCommand = Cmd_AddServerCommand_t(0x4DCE00);
	Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand = Cmd_ExecuteSingleCommand_t(0x609540);
	Cmd_ForEach_t Cmd_ForEach = Cmd_ForEach_t(0x45D680);

	Con_DrawMiniConsole_t Con_DrawMiniConsole = Con_DrawMiniConsole_t(0x464F30);
	Con_DrawSolidConsole_t Con_DrawSolidConsole = Con_DrawSolidConsole_t(0x5A5040);
	Con_CancelAutoComplete_t Con_CancelAutoComplete = Con_CancelAutoComplete_t(0x435580);
	Con_IsDvarCommand_t Con_IsDvarCommand = Con_IsDvarCommand_t(0x5A3FF0);

	DB_AllocStreamPos_t DB_AllocStreamPos = DB_AllocStreamPos_t(0x418380);
	DB_PushStreamPos_t DB_PushStreamPos = DB_PushStreamPos_t(0x458A20);
	DB_PopStreamPos_t DB_PopStreamPos = DB_PopStreamPos_t(0x4D1D60);

	Encode_Init_t Encode_Init = Encode_Init_t(0x462AB0);

	Field_Clear_t Field_Clear = Field_Clear_t(0x437EB0);

	FreeMemory_t FreeMemory = FreeMemory_t(0x4D6640);
	Free_String_t Free_String = Free_String_t(0x470E80);

	Svcmd_EntityList_f_t Svcmd_EntityList_f = Svcmd_EntityList_f_t(0x4B6A70);

	Image_LoadFromFileWithReader_t Image_LoadFromFileWithReader = Image_LoadFromFileWithReader_t(0x53ABF0);
	Image_Release_t Image_Release = Image_Release_t(0x51F010);

	Info_ValueForKey_t Info_ValueForKey = Info_ValueForKey_t(0x47C820);
	Info_Validate_t Info_Validate = Info_Validate_t(0x436AE0);

	Key_SetCatcher_t Key_SetCatcher = Key_SetCatcher_t(0x43BD00);
	Key_RemoveCatcher_t Key_RemoveCatcher = Key_RemoveCatcher_t(0x408260);
	Key_IsCatcherActive_t Key_IsCatcherActive = Key_IsCatcherActive_t(0x4DA010);
	Key_SetBinding_t Key_SetBinding = Key_SetBinding_t(0x494C90);

	LargeLocalInit_t LargeLocalInit = LargeLocalInit_t(0x4A62A0);

	Load_Stream_t Load_Stream = Load_Stream_t(0x470E30);
	Load_XString_t Load_XString = Load_XString_t(0x47FDA0);
	Load_XModelPtr_t Load_XModelPtr = Load_XModelPtr_t(0x4FCA70);
	Load_XModelSurfsFixup_t Load_XModelSurfsFixup = Load_XModelSurfsFixup_t(0x40D7A0);
	Load_XStringArray_t Load_XStringArray = Load_XStringArray_t(0x4977F0);
	Load_XStringCustom_t Load_XStringCustom = Load_XStringCustom_t(0x4E0DD0);
	Load_FxEffectDefHandle_t Load_FxEffectDefHandle = Load_FxEffectDefHandle_t(0x4D9B90);
	Load_FxElemDef_t Load_FxElemDef = Load_FxElemDef_t(0x45AD90);
	Load_GfxImagePtr_t Load_GfxImagePtr = Load_GfxImagePtr_t(0x4C13D0);
	Load_Texture_t Load_Texture = Load_Texture_t(0x51F4E0);
	Load_GfxTextureLoad_t Load_GfxTextureLoad = Load_GfxTextureLoad_t(0x4D3210);
	Load_SndAliasCustom_t Load_SndAliasCustom = Load_SndAliasCustom_t(0x49B6B0);
	Load_MaterialHandle_t Load_MaterialHandle = Load_MaterialHandle_t(0x403960);
	Load_PhysCollmapPtr_t Load_PhysCollmapPtr = Load_PhysCollmapPtr_t(0x47E990);
	Load_PhysPresetPtr_t Load_PhysPresetPtr = Load_PhysPresetPtr_t(0x4FAD30);
	Load_TracerDefPtr_t Load_TracerDefPtr = Load_TracerDefPtr_t(0x493090);
	Load_snd_alias_list_nameArray_t Load_snd_alias_list_nameArray = Load_snd_alias_list_nameArray_t(0x4499F0);

	Menus_CloseAll_t Menus_CloseAll = Menus_CloseAll_t(0x4BA5B0);
	Menus_CloseRequest_t Menus_CloseRequest = Menus_CloseRequest_t(0x430D50);
	Menus_OpenByName_t Menus_OpenByName = Menus_OpenByName_t(0x4CCE60);
	Menus_FindByName_t Menus_FindByName = Menus_FindByName_t(0x487240);
	Menu_IsVisible_t Menu_IsVisible = Menu_IsVisible_t(0x4D77D0);
	Menus_MenuIsInStack_t Menus_MenuIsInStack = Menus_MenuIsInStack_t(0x47ACB0);
	Menu_HandleKey_t Menu_HandleKey = Menu_HandleKey_t(0x4C4A00);
	Menu_GetFocused_t Menu_GetFocused = Menu_GetFocused_t(0x4AFF10);
	Menu_Setup_t Menu_Setup = Menu_Setup_t(0x415AD0);

	MSG_Init_t MSG_Init = MSG_Init_t(0x45FCA0);
	MSG_ReadBit_t MSG_ReadBit = MSG_ReadBit_t(0x476D20);
	MSG_ReadBits_t MSG_ReadBits = MSG_ReadBits_t(0x4C3900);
	MSG_ReadData_t MSG_ReadData = MSG_ReadData_t(0x4527C0);
	MSG_ReadLong_t MSG_ReadLong = MSG_ReadLong_t(0x4C9550);
	MSG_ReadShort_t MSG_ReadShort = MSG_ReadShort_t(0x40BDD0);
	MSG_ReadInt64_t MSG_ReadInt64 = MSG_ReadInt64_t(0x4F1850);
	MSG_ReadBigString_t  MSG_ReadBigString = MSG_ReadBigString_t(0x60E2B0);
	MSG_ReadStringLine_t MSG_ReadStringLine = MSG_ReadStringLine_t(0x4FEF30);
	MSG_WriteByte_t MSG_WriteByte = MSG_WriteByte_t(0x48C520);
	MSG_WriteData_t MSG_WriteData = MSG_WriteData_t(0x4F4120);
	MSG_WriteLong_t MSG_WriteLong = MSG_WriteLong_t(0x41CA20);
	MSG_WriteShort_t MSG_WriteShort = MSG_WriteShort_t(0x503B90);
	MSG_WriteString_t MSG_WriteString = MSG_WriteString_t(0x463820);
	MSG_Discard_t MSG_Discard = MSG_Discard_t(0x4F56D0);
	MSG_ReadByte_t MSG_ReadByte = MSG_ReadByte_t(0x4C1C20);
	MSG_ReadDeltaUsercmdKey_t MSG_ReadDeltaUsercmdKey = MSG_ReadDeltaUsercmdKey_t(0x491F00);
	MSG_ReadBitsCompress_t MSG_ReadBitsCompress = MSG_ReadBitsCompress_t(0x4DCC30);
	MSG_WriteBitsCompress_t MSG_WriteBitsCompress = MSG_WriteBitsCompress_t(0x4319D0);
	Huff_offsetReceive_t Huff_offsetReceive = Huff_offsetReceive_t(0x466060);

	NetadrToSockadr_t NetadrToSockadr = NetadrToSockadr_t(0x4B4B40);

	NET_AdrToString_t NET_AdrToString = NET_AdrToString_t(0x469880);
	NET_CompareAdr_t NET_CompareAdr = NET_CompareAdr_t(0x4D0AA0);
	NET_CompareBaseAdr_t NET_CompareBaseAdr = NET_CompareBaseAdr_t(0x455510);
	NET_DeferPacketToClient_t NET_DeferPacketToClient = NET_DeferPacketToClient_t(0x4C8AA0);
	NET_ErrorString_t NET_ErrorString = NET_ErrorString_t(0x4E7720);
	NET_Init_t NET_Init = NET_Init_t(0x491860);
	NET_IsLocalAddress_t NET_IsLocalAddress = NET_IsLocalAddress_t(0x402BD0);
	NET_StringToAdr_t NET_StringToAdr = NET_StringToAdr_t(0x409010);
	NET_OutOfBandPrint_t NET_OutOfBandPrint = NET_OutOfBandPrint_t(0x4AEF00);
	NET_OutOfBandData_t NET_OutOfBandData = NET_OutOfBandData_t(0x49C7E0);
	NET_OutOfBandVoiceData_t NET_OutOfBandVoiceData = NET_OutOfBandVoiceData_t(0x4FCC90);

	Live_MPAcceptInvite_t Live_MPAcceptInvite = Live_MPAcceptInvite_t(0x420A6D);
	Live_GetMapIndex_t Live_GetMapIndex = Live_GetMapIndex_t(0x4F6440);
	Live_GetPrestige_t Live_GetPrestige = Live_GetPrestige_t(0x430F90);
	Live_GetXp_t Live_GetXp = Live_GetXp_t(0x404C60);
	Live_GetLocalClientName_t Live_GetLocalClientName = Live_GetLocalClientName_t(0x441FC0);
	Live_IsSystemUiActive_t Live_IsSystemUiActive = Live_IsSystemUiActive_t(0x4F5CB0);

	LiveStorage_GetStat_t LiveStorage_GetStat = LiveStorage_GetStat_t(0x471F60);
	LiveStorage_SetStat_t LiveStorage_SetStat = LiveStorage_SetStat_t(0x4CC5D0);

	Scr_AddSourceBuffer_t Scr_AddSourceBuffer = Scr_AddSourceBuffer_t(0x61ABC0);

	Party_GetMaxPlayers_t Party_GetMaxPlayers = Party_GetMaxPlayers_t(0x4F5D60);
	PartyHost_CountMembers_t PartyHost_CountMembers = PartyHost_CountMembers_t(0x497330);
	PartyHost_GetMemberAddressBySlot_t PartyHost_GetMemberAddressBySlot = PartyHost_GetMemberAddressBySlot_t(0x44E100);
	PartyHost_GetMemberName_t PartyHost_GetMemberName = PartyHost_GetMemberName_t(0x44BE90);
	Party_InParty_t Party_InParty = Party_InParty_t(0x4F10C0);

	Playlist_ParsePlaylists_t Playlist_ParsePlaylists = Playlist_ParsePlaylists_t(0x4295A0);

	R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic = R_AddCmdDrawStretchPic_t(0x509770);
	R_AllocStaticIndexBuffer_t R_AllocStaticIndexBuffer = R_AllocStaticIndexBuffer_t(0x51E7A0);
	R_Cinematic_StartPlayback_Now_t R_Cinematic_StartPlayback_Now = R_Cinematic_StartPlayback_Now_t(0x51C5B0);
	R_RegisterFont_t R_RegisterFont = R_RegisterFont_t(0x505670);
	R_AddCmdDrawText_t R_AddCmdDrawText = R_AddCmdDrawText_t(0x509D80);
	R_LoadGraphicsAssets_t R_LoadGraphicsAssets = R_LoadGraphicsAssets_t(0x506AC0);
	R_TextWidth_t R_TextWidth = R_TextWidth_t(0x5056C0);
	R_TextHeight_t R_TextHeight = R_TextHeight_t(0x505770);
	R_FlushSun_t R_FlushSun = R_FlushSun_t(0x53FB50);
	R_SortWorldSurfaces_t R_SortWorldSurfaces = R_SortWorldSurfaces_t(0x53DC10);

	GetMemory_t GetMemory = GetMemory_t(0x4E67B0);
	GetClearedMemory_t GetClearedMemory = GetClearedMemory_t(0x422E70);
	PS_CreatePunctuationTable_t PS_CreatePunctuationTable = PS_CreatePunctuationTable_t(0x4E6950);
	free_expression_t free_expression = free_expression_t(0x4ACC70);

	SE_Load_t SE_Load = SE_Load_t(0x502A30);

	SEH_StringEd_GetString_t SEH_StringEd_GetString = SEH_StringEd_GetString_t(0x44BB30);
	SEH_ReadCharFromString_t SEH_ReadCharFromString = SEH_ReadCharFromString_t(0x486560);
	SEH_GetCurrentLanguage_t SEH_GetCurrentLanguage = SEH_GetCurrentLanguage_t(0x4F6110);

	SND_Init_t SND_Init = SND_Init_t(0x46A630);
	SND_InitDriver_t SND_InitDriver = SND_InitDriver_t(0x4F5090);

	SockadrToNetadr_t SockadrToNetadr = SockadrToNetadr_t(0x4F8460);

	Steam_JoinLobby_t Steam_JoinLobby = Steam_JoinLobby_t(0x49CF70);

	TeleportPlayer_t TeleportPlayer = TeleportPlayer_t(0x496850);

	UI_AddMenuList_t UI_AddMenuList = UI_AddMenuList_t(0x4533C0);
	UI_GetActiveMenu_t UI_GetActiveMenu = UI_GetActiveMenu_t(0x4BE790);
	UI_CheckStringTranslation_t UI_CheckStringTranslation = UI_CheckStringTranslation_t(0x4FB010);
	UI_LoadMenus_t UI_LoadMenus = UI_LoadMenus_t(0x641460);
	UI_UpdateArenas_t UI_UpdateArenas = UI_UpdateArenas_t(0x4A95B0);
	UI_SortArenas_t UI_SortArenas = UI_SortArenas_t(0x630AE0);
	UI_DrawHandlePic_t UI_DrawHandlePic = UI_DrawHandlePic_t(0x4D0EA0);
	ScrPlace_GetActivePlacement_t ScrPlace_GetActivePlacement = ScrPlace_GetActivePlacement_t(0x4F8940);
	UI_TextWidth_t UI_TextWidth = UI_TextWidth_t(0x6315C0);
	UI_TextHeight_t UI_TextHeight = UI_TextHeight_t(0x4C8630);
	UI_DrawText_t UI_DrawText = UI_DrawText_t(0x49C0D0);
	UI_GetFontHandle_t UI_GetFontHandle = UI_GetFontHandle_t(0x4AEA60);
	ScrPlace_ApplyRect_t ScrPlace_ApplyRect = ScrPlace_ApplyRect_t(0x454E20);
	UI_KeyEvent_t UI_KeyEvent = UI_KeyEvent_t(0x4970F0);
	UI_SafeTranslateString_t UI_SafeTranslateString = UI_SafeTranslateString_t(0x4F1700);
	UI_ReplaceConversions_t UI_ReplaceConversions = UI_ReplaceConversions_t(0x4E9740);
	UI_ParseInfos_t UI_ParseInfos = UI_ParseInfos_t(0x4027A0);
	UI_GetMapDisplayName_t UI_GetMapDisplayName = UI_GetMapDisplayName_t(0x420700);
	UI_GetGameTypeDisplayName_t UI_GetGameTypeDisplayName = UI_GetGameTypeDisplayName_t(0x4EB0B0);
	ParseConfigStringToStruct_t ParseConfigStringToStruct = ParseConfigStringToStruct_t(0x403B60);

	Win_GetLanguage_t Win_GetLanguage = Win_GetLanguage_t(0x45CBA0);

	Vec3UnpackUnitVec_t Vec3UnpackUnitVec = Vec3UnpackUnitVec_t(0x45CA90);
	vectoryaw_t vectoryaw = vectoryaw_t(0x45AD10);
	AngleNormalize360_t AngleNormalize360 = AngleNormalize360_t(0x438DC0);
	_VectorMA_t _VectorMA = _VectorMA_t(0x5084D0);

	unzClose_t unzClose = unzClose_t(0x41BF20);

	RB_DrawCursor_t RB_DrawCursor = RB_DrawCursor_t(0x534EA0);

	R_NormalizedTextScale_t R_NormalizedTextScale = R_NormalizedTextScale_t(0x5056A0);

	Material_Process2DTextureCoordsForAtlasing_t Material_Process2DTextureCoordsForAtlasing = Material_Process2DTextureCoordsForAtlasing_t(0x506090);

	Byte4PackRgba_t Byte4PackRgba = Byte4PackRgba_t(0x4FE910);
	RandWithSeed_t RandWithSeed = RandWithSeed_t(0x495580);
	GetDecayingLetterInfo_t GetDecayingLetterInfo = GetDecayingLetterInfo_t(0x5351C0);

	Field_Draw_t Field_Draw = Field_Draw_t(0x4F5B40);
	Field_AdjustScroll_t Field_AdjustScroll = Field_AdjustScroll_t(0x488C10);
	AimAssist_ApplyAutoMelee_t AimAssist_ApplyAutoMelee = AimAssist_ApplyAutoMelee_t(0x56A360);

	Weapon_RocketLauncher_Fire_t Weapon_RocketLauncher_Fire = Weapon_RocketLauncher_Fire_t(0x424680);
	Bullet_Fire_t Bullet_Fire = Bullet_Fire_t(0x4402C0);

	FireWeapon_t FireWeapon = FireWeapon_t(0x4A4D50);
	FireWeaponMelee_t FireWeaponMelee = FireWeaponMelee_t(0x4F2470);
	GetClientPositionAtTime_t GetClientPositionAtTime = GetClientPositionAtTime_t(0x455960);
	SV_LinkEntity_t SV_LinkEntity = SV_LinkEntity_t(0x4E0880);
	OnSameTeam_t OnSameTeam = OnSameTeam_t(0x4BEB80);
	Melee_Trace_t Melee_Trace = Melee_Trace_t(0x5FCCF0);
	G_RunItem_t G_GeneralLink = G_RunItem_t(0x43B9D0);
	G_RunThink_t G_RunThink = G_RunThink_t(0x43EC40);

	G_RunMissileInternal_t G_RunMissileInternal = G_RunMissileInternal_t(0x5E8BE0);

	Bullet_GetMethodOfDeath_t Bullet_GetMethodOfDeath = Bullet_GetMethodOfDeath_t(0x4A0420);
	Bullet_Endpos_t Bullet_Endpos = Bullet_Endpos_t(0x4D1A50);
	BG_WeaponBulletFire_ShouldPenetrate_t BG_WeaponBulletFire_ShouldPenetrate = BG_WeaponBulletFire_ShouldPenetrate_t(0x4B5380);
	BG_WeaponBulletFire_ShouldSpread_t BG_WeaponBulletFire_ShouldSpread = BG_WeaponBulletFire_ShouldSpread_t(0x4D7D90);
	Bullet_PenetrationTrace_t Bullet_FirePenetrate = Bullet_PenetrationTrace_t(0x5D60D0);
	Bullet_SpreadTrace_t Bullet_FireExtended = Bullet_SpreadTrace_t(0x5D5F50);
	Bullet_ShotgunSpread_t Bullet_ShotgunSpread = Bullet_ShotgunSpread_t(0x5D6860);

	Trace_GetEntityHitId_t Trace_GetEntityHitId = Trace_GetEntityHitId_t(0x501F90);
	G_ShieldNotifyAndDamage_t G_ShieldNotifyAndDamage = G_ShieldNotifyAndDamage_t(0x4BFA10);
	G_Damage_t G_Damage = G_Damage_t(0x418600);
	Melee_Trace_Internal_t Melee_Trace_Internal = Melee_Trace_Internal_t(0x5FC8A0);

	IN_RecenterMouse_t IN_RecenterMouse = IN_RecenterMouse_t(0x463D80);

	IN_MouseMove_t IN_MouseMove = IN_MouseMove_t(0x64C490);
	IN_MouseEvent_t IN_MouseEvent = IN_MouseEvent_t(0x4C84D0);
	IN_Frame_t IN_Frame = IN_Frame_t(0x475E10);
	IN_Init_t IN_Init = IN_Init_t(0x45D620);
	IN_Shutdown_t IN_Shutdown = IN_Shutdown_t(0x426360);

	Touch_Item_t Touch_Item = Touch_Item_t(0x44FA20);

	Add_Ammo_t Add_Ammo = Add_Ammo_t(0x4E1480);

	ClientUserinfoChanged_t ClientUserinfoChanged = ClientUserinfoChanged_t(0x445240);

	player_die_t player_die = player_die_t(0x42BC70);

	Vec3Normalize_t Vec3Normalize = Vec3Normalize_t(0x453500);
	Vec3NormalizeFast_t Vec3NormalizeFast = Vec3NormalizeFast_t(0x478F80);
	Vec2Normalize_t Vec2Normalize = Vec2Normalize_t(0x416F70);
	Vec2NormalizeFast_t Vec2NormalizeFast = Vec2NormalizeFast_t(0x5FC830);

	I_strncpyz_t I_strncpyz = I_strncpyz_t(0x4D6F80);
	I_CleanStr_t I_CleanStr = I_CleanStr_t(0x4AD470);
	I_isdigit_t I_isdigit = I_isdigit_t(0x4E71E0);

	XNAddrToString_t XNAddrToString = XNAddrToString_t(0x452690);

	Voice_IncomingVoiceData_t Voice_IncomingVoiceData = Voice_IncomingVoiceData_t(0x5001A0);
	Voice_IsClientTalking_t Voice_IsClientTalking = Voice_IsClientTalking_t(0x4D9D20);

	LargeLocalBegin_t LargeLocalBegin = LargeLocalBegin_t(0x4127A0);
	LargeLocalBeginRight_t LargeLocalBeginRight = LargeLocalBeginRight_t(0x644140);
	LargeLocalReset_t LargeLocalReset = LargeLocalReset_t(0x430630);

	StructuredDataDef_GetAsset_t StructuredDataDef_GetAsset = StructuredDataDef_GetAsset_t(0x4D5C50);

	StringTable_Lookup_t StringTable_Lookup = StringTable_Lookup_t(0x42F0E0);
	StringTable_HashString_t StringTable_HashString = StringTable_HashString_t(0x475EB0);
	StringTable_GetAsset_FastFile_t StringTable_GetAsset_FastFile = StringTable_GetAsset_FastFile_t(0x41A0B0);
	StringTable_LookupRowNumForValue_t StringTable_LookupRowNumForValue = StringTable_LookupRowNumForValue_t(0x4AC180);
	StringTable_GetColumnValueForRow_t StringTable_GetColumnValueForRow = StringTable_GetColumnValueForRow_t(0x4F2C80);

	longjmp_internal_t longjmp_internal = longjmp_internal_t(0x6B8898);

	CmdArgs* cmd_args = reinterpret_cast<CmdArgs*>(0x1AAC5D0);
	CmdArgs* sv_cmd_args = reinterpret_cast<CmdArgs*>(0x1ACF8A0);

	cmd_function_s** cmd_functions = reinterpret_cast<cmd_function_s**>(0x1AAC658);

	source_s** sourceFiles = reinterpret_cast<source_s**>(0x7C4A98);

	float* cgameFOVSensitivityScale = reinterpret_cast<float*>(0xB2F884);

	UiContext* uiContext = reinterpret_cast<UiContext*>(0x62E2858);
	UiContext* cgDC = reinterpret_cast<Game::UiContext*>(0x7DEDB8);
	const ExpressionSupportingData* menuSupportingData = reinterpret_cast<Game::ExpressionSupportingData*>(0x62D2270);

	int* arenaCount = reinterpret_cast<int*>(0x62E6930);
	mapArena_t* arenas = reinterpret_cast<mapArena_t*>(0x62E6934);

	int* gameTypeCount = reinterpret_cast<int*>(0x62E50A0);
	gameTypeName_t* gameTypes = reinterpret_cast<gameTypeName_t*>(0x62E50A4);

	bool* g_lobbyCreateInProgress = reinterpret_cast<bool*>(0x66C9BC2);
	PartyData* g_lobbyData = reinterpret_cast<PartyData*>(0x1081C00);
	PartyData* g_partyData = reinterpret_cast<PartyData*>(0x107E500);

	SessionData* g_serverSession = reinterpret_cast<SessionData*>(0x66B7008);

	int* numIP = reinterpret_cast<int*>(0x64A1E68);
	netIP_t* localIP = reinterpret_cast<netIP_t*>(0x64A1E28);

	netadr_t* connectedHost = reinterpret_cast<netadr_t*>(0xA1E888);

	SOCKET* ip_socket = reinterpret_cast<SOCKET*>(0x64A3008);

	SafeArea* safeArea = reinterpret_cast<SafeArea*>(0xA15F3C);

	SpawnVar* spawnVars = reinterpret_cast<SpawnVar*>(0x1A83DE8);
	MapEnts** marMapEntsPtr = reinterpret_cast<MapEnts**>(0x112AD34);

	IDirect3D9** d3d9 = reinterpret_cast<IDirect3D9**>(0x66DEF84);
	IDirect3DDevice9** dx_ptr = reinterpret_cast<IDirect3DDevice9**>(0x66DEF88);

	mapname_t* mapnames = reinterpret_cast<mapname_t*>(0x7471D0);

	char*** varXString = reinterpret_cast<char***>(0x112B340);
	TracerDef*** varTracerDefPtr = reinterpret_cast<TracerDef***>(0x112B3BC);
	XModel*** varXModelPtr = reinterpret_cast<XModel***>(0x112A934);
	XModel** varXModel = reinterpret_cast<XModel**>(0x112AE14);
	PathData** varPathData = reinterpret_cast<PathData**>(0x112AD7C);
	const char** varConstChar = reinterpret_cast<const char**>(0x112A774);
	Material*** varMaterialHandle = reinterpret_cast<Material***>(0x112A878);
	FxEffectDef*** varFxEffectDefHandle = reinterpret_cast<FxEffectDef***>(0x112ACC0);
	PhysCollmap*** varPhysCollmapPtr = reinterpret_cast<PhysCollmap***>(0x112B440);
	PhysPreset*** varPhysPresetPtr = reinterpret_cast<PhysPreset***>(0x112B378);
	MaterialPass** varMaterialPass = reinterpret_cast<MaterialPass**>(0x112A960);
	snd_alias_list_t*** varsnd_alias_list_name = reinterpret_cast<snd_alias_list_t***>(0x112AF38);
	MaterialVertexShader** varMaterialVertexShader = reinterpret_cast<MaterialVertexShader**>(0x112B338);

	FxElemField* s_elemFields = reinterpret_cast<FxElemField*>(0x73B848);

	visField_t* visionDefFields = reinterpret_cast<visField_t*>(0x7982F0); // Count 21

	infoParm_t* infoParams = reinterpret_cast<infoParm_t*>(0x79D260); // Count 0x1E

	GfxScene* scene = reinterpret_cast<GfxScene*>(0x6944914);

	Console* con = reinterpret_cast<Console*>(0x9FCCF8);
	ConDrawInputGlob* conDrawInputGlob = reinterpret_cast<ConDrawInputGlob*>(0x9FD6F8);

	int* g_console_field_width = reinterpret_cast<int*>(0x79854C);
	float* g_console_char_height = reinterpret_cast<float*>(0x798550);
	field_t* g_consoleField = reinterpret_cast<field_t*>(0xA1B6B0);

	sharedUiInfo_t* sharedUiInfo = reinterpret_cast<sharedUiInfo_t*>(0x62E4B78);
	ScreenPlacement* scrPlaceFull = reinterpret_cast<ScreenPlacement*>(0x10843F0);
	ScreenPlacement* scrPlaceFullUnsafe = reinterpret_cast<ScreenPlacement*>(0x1084460);
	ScreenPlacement* scrPlaceView = reinterpret_cast<ScreenPlacement*>(0x1084378);

	PlayerKeyState* playerKeys = reinterpret_cast<PlayerKeyState*>(0xA1B7D0);
	kbutton_t* playersKb = reinterpret_cast<kbutton_t*>(0xA1A9A8);
	AimAssistGlobals* aaGlobArray = reinterpret_cast<AimAssistGlobals*>(0x7A2110);

	keyname_t* keyNames = reinterpret_cast<keyname_t*>(0x798580);
	keyname_t* localizedKeyNames = reinterpret_cast<keyname_t*>(0x798880);

	GraphFloat* aaInputGraph = reinterpret_cast<GraphFloat*>(0x7A2FC0);

	const char* MY_CMDS = reinterpret_cast<const char*>(0x73C9C4); // Count 5

	XModel** cached_models = reinterpret_cast<XModel**>(0x1AA20C8);

	float (*CorrectSolidDeltas)[26][3] = reinterpret_cast<float(*)[26][3]>(0x739BB8); // Count 26

	level_locals_t* level = reinterpret_cast<level_locals_t*>(0x1A831A8);

	float (*penetrationDepthTable)[PENETRATE_TYPE_COUNT][SURF_TYPE_COUNT] = reinterpret_cast<float(*)[PENETRATE_TYPE_COUNT][SURF_TYPE_COUNT]>(0x7C4878);

	WinMouseVars_t* s_wmv = reinterpret_cast<WinMouseVars_t*>(0x649D640);

	int* window_center_x = reinterpret_cast<int*>(0x649D638);
	int* window_center_y = reinterpret_cast<int*>(0x649D630);

	DeferredQueue* deferredQueue = reinterpret_cast<DeferredQueue*>(0x1CC2CE8);

	int* g_waitingForKey = reinterpret_cast<int*>(0x63A50FC);

	Material** whiteMaterial = reinterpret_cast<Material**>(0x8EE4B8);

	unsigned long* g_dwTlsIndex = reinterpret_cast<unsigned long*>(0x66D94A8);

	bgs_t* level_bgs = reinterpret_cast<bgs_t*>(0x19BD680);

	unsigned int* playerCardUIStringIndex = reinterpret_cast<unsigned int*>(0x62CD7A8);
	char (*playerCardUIStringBuf)[PLAYER_CARD_UI_STRING_COUNT][38] = reinterpret_cast<char(*)[PLAYER_CARD_UI_STRING_COUNT][38]>(0x62CB4F8);

	uiInfo_s* uiInfoArray = reinterpret_cast<uiInfo_s*>(0x62E2858);

	int* logfile = reinterpret_cast<int*>(0x1AD8F28);

	GamerSettingState* gamerSettings = reinterpret_cast<GamerSettingState*>(0x107D3E8);

	unsigned char* g_largeLocalBuf = reinterpret_cast<unsigned char*>(0x63D9790);
	int* g_largeLocalPos = reinterpret_cast<int*>(0x63D97B4);
	int* g_largeLocalRightPos = reinterpret_cast<int*>(0x63D9780);

	char** ui_arenaInfos = reinterpret_cast<char**>(0x62D2688);
	int* ui_numArenas = reinterpret_cast<int*>(0x62D2788);
	int* ui_arenaBufPos = reinterpret_cast<int*>(0x62D278C);

	punctuation_s* default_punctuations = reinterpret_cast<punctuation_s*>(0x797F80);
	int* numtokens = reinterpret_cast<int*>(0x7C4BA0);

	bool* s_havePlaylists = reinterpret_cast<bool*>(0x1AD3680);

	huffman_t* msgHuff = reinterpret_cast<huffman_t*>(0x1CB9EC0);

	const char* TableLookup(StringTable* stringtable, int row, int column)
	{
		if (!stringtable || !stringtable->values || row >= stringtable->rowCount || column >= stringtable->columnCount) return "";

		const char* value = stringtable->values[row * stringtable->columnCount + column].string;
		if (!value) value = "";

		return value;
	}

	const char* UI_LocalizeGameType(const char* gameType)
	{
		if (!gameType || !*gameType)
		{
			return "";
		}

		for (int i = 0; i < *gameTypeCount; ++i)
		{
			if (!_stricmp(gameTypes[i].gameType, gameType))
			{
				return SEH_StringEd_GetString(gameTypes[i].uiName);
			}
		}

		return gameType;
	}

	// this cant be MessageBox because windows.h has a define that converts it to MessageBoxW. which is just stupid
	void ShowMessageBox(const std::string& message, const std::string& title)
	{
		if (!CL_IsCgameInitialized())
		{
			Dvar_SetStringByName("com_errorMessage", message.data());
			Dvar_SetStringByName("com_errorTitle", title.data());
			Cbuf_AddText(0, "openmenu error_popmenu_lobby\n");
		}
	}

	unsigned int R_HashString(const char* string)
	{
		unsigned int hash = 0;

		while (*string)
		{
			hash = (*string | 0x20) ^ (33 * hash);
			++string;
		}

		return hash;
	}

	unsigned int R_HashString(const char* string, size_t maxLen)
	{
		unsigned int hash = 0;

		while (*string && maxLen > 0)
		{
			hash = (*string | 0x20) ^ (33 * hash);
			++string;
			maxLen--;
		}

		return hash;
	}

	void Load_IndexBuffer(void* data, IDirect3DIndexBuffer9** storeHere, int count)
	{
		if (Components::Dvar::Var("r_loadForRenderer").get<bool>())
		{
			void* buffer = R_AllocStaticIndexBuffer(storeHere, 2 * count);
			std::memcpy(buffer, data, 2 * count);

			if (storeHere && *storeHere)
			{
				(*storeHere)->Unlock();
			}
		}
	}

	void Vec2UnpackTexCoords(const PackedTexCoords in, vec2_t* out)
	{
		unsigned int v3; // xmm1_4

		if (LOWORD(in.packed))
			v3 = ((in.packed & 0x8000) << 16) | (((((in.packed & 0x3FFF) << 14) - (~(LOWORD(in.packed) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
		else
			v3 = 0;

		(*out)[0] = *reinterpret_cast<float*>(&v3);

		if (HIWORD(in.packed))
			v3 = ((HIWORD(in.packed) & 0x8000) << 16) | (((((HIWORD(in.packed) & 0x3FFF) << 14)
				- (~(HIWORD(in.packed) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
		else
			v3 = 0;

		(*out)[1] = *reinterpret_cast<float*>(&v3);
	}

	void MatrixVecMultiply(const float (& mulMat)[3][3], const vec3_t& mulVec, vec3_t& solution)
	{
		vec3_t res;
		res[0] = mulMat[0][0] * mulVec[0] + mulMat[1][0] * mulVec[1] + mulMat[2][0] * mulVec[2];
		res[1] = mulMat[0][1] * mulVec[0] + mulMat[1][1] * mulVec[1] + mulMat[2][1] * mulVec[2];
		res[2] = mulMat[0][2] * mulVec[0] + mulMat[1][2] * mulVec[1] + mulMat[2][2] * mulVec[2];
		std::memmove(&solution[0], &res[0], sizeof(res));
	}

	void QuatRot(vec3_t* vec, const vec4_t* quat)
	{
		vec4_t q{ (*quat)[3],(*quat)[0],(*quat)[1],(*quat)[2] };

		vec4_t res{ 0, (*vec)[0], (*vec)[1], (*vec)[2] };
		vec4_t res2;
		vec4_t quat_conj{ q[0], -q[1], -q[2], -q[3] };
		QuatMultiply(&q, &res, &res2);
		QuatMultiply(&res2, &quat_conj, &res);

		(*vec)[0] = res[1];
		(*vec)[1] = res[2];
		(*vec)[2] = res[3];
	}

	void QuatMultiply(const vec4_t* q1, const vec4_t* q2, vec4_t* res)
	{
		(*res)[0] = (*q2)[0] * (*q1)[0] - (*q2)[1] * (*q1)[1] - (*q2)[2] * (*q1)[2] - (*q2)[3] * (*q1)[3];
		(*res)[1] = (*q2)[0] * (*q1)[1] + (*q2)[1] * (*q1)[0] - (*q2)[2] * (*q1)[3] + (*q2)[3] * (*q1)[2];
		(*res)[2] = (*q2)[0] * (*q1)[2] + (*q2)[1] * (*q1)[3] + (*q2)[2] * (*q1)[0] - (*q2)[3] * (*q1)[1];
		(*res)[3] = (*q2)[0] * (*q1)[3] - (*q2)[1] * (*q1)[2] + (*q2)[2] * (*q1)[1] + (*q2)[3] * (*q1)[0];
	}

	void SortWorldSurfaces(GfxWorld* world)
	{
		DWORD* specular1 = reinterpret_cast<DWORD*>(0x69F105C);
		DWORD* specular2 = reinterpret_cast<DWORD*>(0x69F92D4);
		DWORD saveSpecular1 = *specular1;
		DWORD saveSpecular2 = *specular2;

		GfxWorld** gameWorld = reinterpret_cast<GfxWorld**>(0x66DEE94);
		GfxWorld* saveWorld = *gameWorld;

		*specular1 = 1;
		*specular2 = 1;
		*gameWorld = world;

		R_SortWorldSurfaces();

		*gameWorld = saveWorld;
		*specular1 = saveSpecular1;
		*specular2 = saveSpecular2;
	}

	void R_AddDebugBounds(float* color, Bounds* b)
	{
		vec3_t v1, v2, v3, v4, v5, v6, v7, v8;
		float* center = b->midPoint;
		float* halfSize = b->halfSize;

		v1[0] = center[0] - halfSize[0];
		v1[1] = center[1] - halfSize[1];
		v1[2] = center[2] - halfSize[2];

		v2[0] = center[0] + halfSize[0];
		v2[1] = center[1] - halfSize[1];
		v2[2] = center[2] - halfSize[2];

		v3[0] = center[0] - halfSize[0];
		v3[1] = center[1] + halfSize[1];
		v3[2] = center[2] - halfSize[2];

		v4[0] = center[0] + halfSize[0];
		v4[1] = center[1] + halfSize[1];
		v4[2] = center[2] - halfSize[2];

		v5[0] = center[0] - halfSize[0];
		v5[1] = center[1] - halfSize[1];
		v5[2] = center[2] + halfSize[2];

		v6[0] = center[0] + halfSize[0];
		v6[1] = center[1] - halfSize[1];
		v6[2] = center[2] + halfSize[2];

		v7[0] = center[0] - halfSize[0];
		v7[1] = center[1] + halfSize[1];
		v7[2] = center[2] + halfSize[2];

		v8[0] = center[0] + halfSize[0];
		v8[1] = center[1] + halfSize[1];
		v8[2] = center[2] + halfSize[2];

		// bottom
		R_AddDebugLine(color, v1, v2);
		R_AddDebugLine(color, v2, v4);
		R_AddDebugLine(color, v4, v3);
		R_AddDebugLine(color, v3, v1);

		// top
		R_AddDebugLine(color, v5, v6);
		R_AddDebugLine(color, v6, v8);
		R_AddDebugLine(color, v8, v7);
		R_AddDebugLine(color, v7, v5);

		// verticals
		R_AddDebugLine(color, v1, v5);
		R_AddDebugLine(color, v2, v6);
		R_AddDebugLine(color, v3, v7);
		R_AddDebugLine(color, v4, v8);
	}

	void R_AddDebugBounds(float* color, Bounds* b, const float(*quat)[4])
	{
		vec3_t v[8];
		auto* center = b->midPoint;
		auto* halfSize = b->halfSize;

		v[0][0] = -halfSize[0];
		v[0][1] = -halfSize[1];
		v[0][2] = -halfSize[2];

		v[1][0] = halfSize[0];
		v[1][1] = -halfSize[1];
		v[1][2] = -halfSize[2];

		v[2][0] = -halfSize[0];
		v[2][1] = halfSize[1];
		v[2][2] = -halfSize[2];

		v[3][0] = halfSize[0];
		v[3][1] = halfSize[1];
		v[3][2] = -halfSize[2];

		v[4][0] = -halfSize[0];
		v[4][1] = -halfSize[1];
		v[4][2] = halfSize[2];

		v[5][0] = halfSize[0];
		v[5][1] = -halfSize[1];
		v[5][2] = halfSize[2];

		v[6][0] = -halfSize[0];
		v[6][1] = halfSize[1];
		v[6][2] = halfSize[2];

		v[7][0] = halfSize[0];
		v[7][1] = halfSize[1];
		v[7][2] = halfSize[2];

		for(auto& vec : v)
		{
			QuatRot(&vec, quat);
			vec[0] += center[0];
			vec[1] += center[1];
			vec[2] += center[2];
		}

		// bottom
		R_AddDebugLine(color, v[0], v[1]);
		R_AddDebugLine(color, v[1], v[3]);
		R_AddDebugLine(color, v[3], v[2]);
		R_AddDebugLine(color, v[2], v[0]);

		// top
		R_AddDebugLine(color, v[4], v[5]);
		R_AddDebugLine(color, v[5], v[7]);
		R_AddDebugLine(color, v[7], v[6]);
		R_AddDebugLine(color, v[6], v[4]);

		// verticals
		R_AddDebugLine(color, v[0], v[4]);
		R_AddDebugLine(color, v[1], v[5]);
		R_AddDebugLine(color, v[2], v[6]);
		R_AddDebugLine(color, v[3], v[7]);
	}

	float GraphGetValueFromFraction(const int knotCount, const float(*knots)[2], const float fraction)
	{
		for (auto knotIndex = 1; knotIndex < knotCount; ++knotIndex)
		{
			if (knots[knotIndex][0] >= fraction)
			{
				const auto adjustedFraction = (fraction - knots[knotIndex - 1][0]) / (knots[knotIndex][0] - knots[knotIndex - 1][0]);

				return (knots[knotIndex][1] - knots[knotIndex - 1][1]) * adjustedFraction + knots[knotIndex - 1][1];
			}
		}

		return -1.0f;
	}

	float GraphFloat_GetValue(const GraphFloat* graph, const float fraction)
	{
		return GraphGetValueFromFraction(graph->knotCount, graph->knots, fraction) * graph->scale;
	}

	ScreenPlacement* ScrPlace_GetFullPlacement()
	{
		return scrPlaceFull;
	}

	ScreenPlacement* ScrPlace_GetUnsafeFullPlacement()
	{
		return scrPlaceFullUnsafe;
	}

	void UI_FilterStringForButtonAnimation(char* str, unsigned int strMaxSize)
	{
		if (SEH_GetCurrentLanguage() == 8)
		{
			return;
		}

		const auto remainder = Sys_Milliseconds() % 1000;
		if (remainder <= 800)
		{
			return;
		}

		for (std::size_t idx = 0; str[idx] && idx < strMaxSize; ++idx)
		{
			if (str[idx] == 16)
			{
				str[idx] = -68;
			}
			else if (str[idx] == 17)
			{
				str[idx] = -67;
			}
		}
	}

	void I_strncpyz_s(char* dest, std::size_t destsize, const char* src, std::size_t count)
	{
		if (!destsize && !dest)
		{
			return;
		}
		if (!src || !count)
		{
			*dest = '\0';
		}
		else
		{
			const auto* p = reinterpret_cast<const unsigned char*>(src - 1);
			auto* q = reinterpret_cast<unsigned char*>(dest - 1);
			auto n = count + 1;
			auto s = count;
			if (destsize <= count)
			{
				n = destsize + 1;
				s = destsize - 1;
			}
			do
			{
				if (!--n)
				{
					dest[s] = '\0';
					return;
				}
				*++q = *++p;
			} while (*q);
		}
	}

	void I_strcpy(char* dest, std::size_t destsize, const char* src)
	{
		I_strncpyz_s(dest, destsize, src, destsize);
	}

	__declspec(naked) float UI_GetScoreboardLeft(void* /*a1*/)
	{
		__asm
		{
			push eax
			pushad

			mov ecx, 590390h
			mov eax, [esp + 28h]
			call ecx
			mov [esp + 20h], eax
			popad
			pop eax

			retn
		}
	}

	__declspec(naked) bool PM_IsAdsAllowed(playerState_s* /*ps*/)
	{
		__asm
		{
			push eax
			pushad

			mov esi, [esp + 0x24 + 0x4] // ps
			mov ecx, 0x5755A0
			call ecx

			mov [esp + 0x20], eax
			popad
			pop eax

			ret
		}
	}

	__declspec(naked) void R_LoadSunThroughDvars(const char* /*mapname*/, sunflare_t* /*sun*/)
	{
		__asm
		{
			pushad
			push [esp + 28h]
			mov eax, [esp + 28h]

			mov ecx, 53F990h
			call ecx

			add esp, 4h
			popad
			retn
		}
	}

	__declspec(naked) void R_SetSunFromDvars(sunflare_t* /*sun*/)
	{
		__asm
		{
			pushad
			mov esi, [esp + 24h]

			mov eax, 53F6D0h
			call eax

			popad
			retn
		}
	}

	__declspec(naked) void IN_KeyUp(kbutton_t* /*button*/)
	{
		__asm
		{
			pushad
			mov esi, [esp + 24h]
			mov eax, 5A5580h
			call eax
			popad
			retn
		}
	}

	__declspec(naked) void IN_KeyDown(kbutton_t* /*button*/)
	{
		__asm
		{
			pushad
			mov esi, [esp + 24h]
			mov eax, 5A54E0h
			call eax
			popad
			retn
		}
	}

	__declspec(naked) void Load_VertexBuffer(void* /*data*/, IDirect3DVertexBuffer9** /*where*/, int /*len*/)
	{
		__asm
		{
			pushad

			mov eax, [esp + 2Ch]
			mov edi, [esp + 28h]
			push [esp + 24h]

			mov ebx, 5112C0h
			call ebx
			add esp, 4

			popad

			retn
		}
	}

	__declspec(naked) void Image_Setup(GfxImage* /*image*/, unsigned int /*width*/, unsigned int /*height*/, unsigned int /*depth*/, unsigned int /*flags*/, _D3DFORMAT /*format*/)
	{
		__asm
		{
			pushad

			mov eax, [esp + 24h] // image
			mov edi, [esp + 28h] // width
			push [esp + 38h]     // format
			push [esp + 38h]     // flags
			push [esp + 38h]     // depth
			push [esp + 38h]     // height

			mov ecx, 54AF50h
			call ecx

			add esp, 10h

			popad
			retn
		}
	}

	void Menu_FreeItem(itemDef_s* item)
	{
		__asm
		{
			pushad

			mov edi, item
			mov ebx, 0x63D880 // Original function address
			call ebx

			popad
		}
	}

	void Menu_SetNextCursorItem(UiContext* a1, menuDef_t* a2, int unk)
	{
		__asm
		{
			push unk
			push a2
			mov eax, a1
			mov ebx, 0x639FE0
			call ebx
			add esp, 0x8 // 2 args = 2x4
		}
	}

	void Menu_SetPrevCursorItem(UiContext* a1, menuDef_t* a2, int unk)
	{
		__asm
		{
			push unk
			push a2
			mov eax, a1
			mov ebx, 0x639F20
			call ebx
			add esp, 0x8 // 2 args = 2x4
		}
	}

	__declspec(naked) void R_AddDebugLine(float* /*color*/, float* /*v1*/, float* /*v2*/)
	{
		__asm
		{
			pushad

			mov eax, [esp + 2Ch] // v2
			push eax

			mov eax, [esp + 2Ch] // v1
			push eax

			// debugglobals
			mov esi, ds:66DAD78h
			add esi, 268772

			mov edi, [esp + 2Ch] // color

			mov eax, 51CEB0h
			call eax

			add esp, 8h

			popad
			retn
		}
	}

	__declspec(naked) void R_AddDebugString(float* /*color*/, float* /*pos*/, float /*scale*/, const char* /*string*/)
	{
		__asm
		{
			pushad

			mov eax, [esp + 30h] // string
			push eax

			mov eax, [esp + 30h] // scale
			push eax

			mov eax, [esp + 2Ch] // color
			push eax

			mov eax, [esp + 34h] // pos
			push eax

			// debugglobals
			mov edi, ds:66DAD78h
			add edi, 268772

			mov eax, 51D0A0h
			call eax

			add esp, 10h

			popad
			retn
		}
	}

	Glyph* R_GetCharacterGlyph(Font_s* font, unsigned int letter)
	{
		static auto R_GetCharacterGlyph_t = 0x5055C0;
		Glyph* result;

		__asm
		{
			pushad

			mov edi, letter
			push font
			call R_GetCharacterGlyph_t
			add esp, 4
			mov result, eax

			popad
		}

		return result;
	}

	__declspec(naked) bool SetupPulseFXVars(const char* /*text*/, int /*maxLength*/, int /*fxBirthTime*/, int /*fxLetterTime*/, int /*fxDecayStartTime*/, int /*fxDecayDuration*/, bool* /*resultDrawRandChar*/, int* /*resultRandSeed*/, int* /*resultMaxLength*/, bool* /*resultDecaying*/, int* /*resultDecayTimeElapsed*/)
	{
		__asm
		{
			push eax
			pushad

			mov eax, [esp + 0x08 + 0x24] // maxLength
			push [esp + 0x2C + 0x24] // resultDecayTimeElapsed
			push [esp + 0x2C + 0x24] // resultDecaying
			push [esp + 0x2C + 0x24] // resultMaxLength
			push [esp + 0x2C + 0x24] // resultRandSeed
			push [esp + 0x2C + 0x24] // resultDrawRandChar
			push [esp + 0x2C + 0x24] // fxDecayDuration
			push [esp + 0x2C + 0x24] // fxDecayStartTime
			push [esp + 0x2C + 0x24] // fxLetterTime
			push [esp + 0x2C + 0x24] // fxBirthTime
			push [esp + 0x28 + 0x24] // text
			mov ebx, 0x535050
			call ebx
			add esp, 0x28
			mov [esp + 0x20],eax

			popad
			pop eax
			ret
		}
	}

	__declspec(naked) void RB_DrawChar(Material* /*material*/, float /*x*/, float /*y*/, float /*w*/, float /*h*/, float /*sinAngle*/, float /*cosAngle*/, Glyph* /*glyph*/, unsigned int /*color*/)
	{
		__asm
		{
			pushad

			mov eax, [esp + 0x4 + 0x20] // material
			mov edx, [esp + 0x20 + 0x20] // glyph
			push [esp + 0x24 + 0x20] // color
			push [esp + 0x20 + 0x20] // cosAngle
			push [esp + 0x20 + 0x20] // sinAngle
			push [esp + 0x20 + 0x20] // h
			push [esp + 0x20 + 0x20] // w
			push [esp + 0x20 + 0x20] // y
			push [esp + 0x20 + 0x20] // x

			mov ecx, 0x534E20
			call ecx
			add esp, 0x1C

			popad
			ret
		}
	}

	__declspec(naked) void RB_DrawStretchPicRotate(Material* /*material*/, float /*x*/, float /*y*/, float /*w*/, float /*h*/, float /*s0*/, float /*t0*/, float /*s1*/, float /*t1*/, float /*sinAngle*/, float /*cosAngle*/, unsigned int /*color*/)
	{
		__asm
		{
			pushad

			mov eax, [esp + 0x4 + 0x20] // material
			push [esp + 0x30 + 0x20] // color
			push [esp + 0x30 + 0x20] // cosAngle
			push [esp + 0x30 + 0x20] // sinAngle
			push [esp + 0x30 + 0x20] // t1
			push [esp + 0x30 + 0x20] // s1
			push [esp + 0x30 + 0x20] // t0
			push [esp + 0x30 + 0x20] // s0
			push [esp + 0x30 + 0x20] // h
			push [esp + 0x30 + 0x20] // w
			push [esp + 0x30 + 0x20] // y
			push [esp + 0x30 + 0x20] // x
			mov ebx, 0x5310F0
			call ebx
			add esp, 0x2C

			popad
			ret
		}
	}

	__declspec(naked) char ModulateByteColors(char /*colorA*/, char /*colorB*/)
	{
		__asm
		{
			push eax
			pushad

			mov eax, [esp + 0x4 + 0x24] // colorA
			mov ecx, [esp + 0x8 + 0x24] // colorB
			mov ebx, 0x5353C0
			call ebx
			mov [esp + 0x20], eax

			popad
			pop eax
			ret
		}
	}

	__declspec(naked) void AimAssist_UpdateTweakables(int /*localClientNum*/)
	{
		__asm
		{
			mov eax, [esp+0x4]
			mov ebx, 0x569950
			call ebx
			retn
		}
	}

	__declspec(naked) void AimAssist_UpdateAdsLerp(const AimInput* /*aimInput*/)
	{
		__asm
		{
			mov eax, [esp + 0x4]
			mov ebx, 0x569AA0
			call ebx
			retn
		}
	}

	constexpr auto ApplyTokenToField_Func = 0x59A760;
	__declspec(naked) bool ApplyTokenToField(unsigned int /*fieldNum*/, const char* /*token*/, visionSetVars_t* /*settings*/)
	{
		__asm
		{
			push eax
			pushad

			mov eax, [esp + 0x24 + 0x4] // fieldNum
			mov ecx, [esp + 0x24 + 0x8] // token
			push [esp + 0x24 + 0xC] // settings
			call ApplyTokenToField_Func
			add esp, 0x4

			movzx eax, al // Zero extend eax
			mov [esp + 0x20], eax
			popad
			pop eax

			ret
		}
	}

	int SEH_GetLocalizedTokenReference(char* token, const char* reference, const char* messageType, msgLocErrType_t errType)
	{
		static DWORD SEH_GetLocalizedTokenReference_t = 0x629BB0;
		auto result = 0;

		__asm
		{
			pushad
			mov esi, reference
			mov edi, messageType
			mov ebx, errType
			push token
			call SEH_GetLocalizedTokenReference_t
			add esp, 0x4
			mov result, eax
			popad
		}

		return result;
	}

	void Player_SwitchToWeapon(gentity_s* player)
	{
		static DWORD Player_SwitchToWeapon_t = 0x5D97B0;

		__asm
		{
			pushad
			mov ebx, player
			call Player_SwitchToWeapon_t
			popad
		}
	}
}
