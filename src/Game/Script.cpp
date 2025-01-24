
namespace Game
{
	AddRefToObject_t AddRefToObject = AddRefToObject_t(0x61C360);
	RemoveRefToObject_t RemoveRefToObject = RemoveRefToObject_t(0x437190);
	RemoveRefToValue_t RemoveRefToValue = RemoveRefToValue_t(0x48E170);
	AllocObject_t AllocObject = AllocObject_t(0x434320);
	AddRefToValue_t AddRefToValue = AddRefToValue_t(0x482740);
	FindVariable_t FindVariable = FindVariable_t(0x4AB650);
	GetVariable_t GetVariable = GetVariable_t(0x419970);
	RemoveVariable_t RemoveVariable = RemoveVariable_t(0x480B40);
	FindObject_t FindObject = FindObject_t(0x4CF2F0);
	GetObject_t GetObject = GetObject_t(0x48B9D0);
	GetNewVariable_t GetNewVariable = GetNewVariable_t(0x4CC520);
	AllocThread_t AllocThread = AllocThread_t(0x4F78C0);

	VM_Execute_0_t VM_Execute_0 = VM_Execute_0_t(0x6222A0);

	Scr_GetGameTypeNameForScript_t Scr_GetGameTypeNameForScript = Scr_GetGameTypeNameForScript_t(0x462460);
	Scr_IsValidGameType_t Scr_IsValidGameType = Scr_IsValidGameType_t(0x4F1B60);
	Scr_LoadGameType_t Scr_LoadGameType = Scr_LoadGameType_t(0x4D9520);
	Scr_StartupGameType_t Scr_StartupGameType = Scr_StartupGameType_t(0x438720);

	Scr_LoadScript_t Scr_LoadScript = Scr_LoadScript_t(0x45D940);
	Scr_ReadFile_FastFile_t Scr_ReadFile_FastFile = Scr_ReadFile_FastFile_t(0x61AAB0);
	Scr_GetFunctionHandle_t Scr_GetFunctionHandle = Scr_GetFunctionHandle_t(0x4234F0);
	Scr_CreateCanonicalFilename_t Scr_CreateCanonicalFilename = Scr_CreateCanonicalFilename_t(0x4A0220);

	Scr_GetString_t Scr_GetString = Scr_GetString_t(0x425900);
	Scr_GetConstString_t Scr_GetConstString = Scr_GetConstString_t(0x494830);
	Scr_GetDebugString_t Scr_GetDebugString = Scr_GetDebugString_t(0x4EBF50);
	Scr_GetFloat_t Scr_GetFloat = Scr_GetFloat_t(0x443140);
	Scr_GetVector_t Scr_GetVector = Scr_GetVector_t(0x411560);
	Scr_GetInt_t Scr_GetInt = Scr_GetInt_t(0x4F31D0);
	Scr_GetObject_t Scr_GetObject = Scr_GetObject_t(0x462100);
	Scr_GetTypeName_t Scr_GetTypeName = Scr_GetTypeName_t(0x4EFF10);
	Scr_GetNumParam_t Scr_GetNumParam = Scr_GetNumParam_t(0x4B0E90);
	Scr_GetEntityId_t Scr_GetEntityId = Scr_GetEntityId_t(0x4165E0);

	Scr_ExecThread_t Scr_ExecThread = Scr_ExecThread_t(0x4AD0B0);
	Scr_FreeThread_t Scr_FreeThread = Scr_FreeThread_t(0x4BD320);

	Scr_AddEntity_t Scr_AddEntity = Scr_AddEntity_t(0x4BFB40);
	Scr_AddString_t Scr_AddString = Scr_AddString_t(0x412310);
	Scr_AddConstString_t Scr_AddConstString = Scr_AddConstString_t(0x488860);
	Scr_AddArray_t Scr_AddArray = Scr_AddArray_t(0x45CE80);
	Scr_MakeArray_t Scr_MakeArray = Scr_MakeArray_t(0x437280);
	Scr_AddIString_t Scr_AddIString = Scr_AddIString_t(0x455F20);
	Scr_AddInt_t Scr_AddInt = Scr_AddInt_t(0x41D7D0);
	Scr_AddFloat_t Scr_AddFloat = Scr_AddFloat_t(0x61E860);
	Scr_AddObject_t Scr_AddObject = Scr_AddObject_t(0x430F40);
	Scr_Notify_t Scr_Notify = Scr_Notify_t(0x4A4750);
	Scr_NotifyLevel_t Scr_NotifyLevel = Scr_NotifyLevel_t(0x4D9C30);

	Scr_ErrorInternal_t Scr_ErrorInternal = Scr_ErrorInternal_t(0x61DB10);
	Scr_Error_t Scr_Error = Scr_Error_t(0x61E8B0);
	Scr_ObjectError_t Scr_ObjectError = Scr_ObjectError_t(0x42EF40);
	Scr_ParamError_t Scr_ParamError = Scr_ParamError_t(0x4FBC70);

	Scr_GetType_t Scr_GetType = Scr_GetType_t(0x422900);
	Scr_GetPointerType_t Scr_GetPointerType = Scr_GetPointerType_t(0x4828E0);

	Scr_ClearOutParams_t Scr_ClearOutParams = Scr_ClearOutParams_t(0x4386E0);

	Scr_GetObjectField_t Scr_GetObjectField = Scr_GetObjectField_t(0x4FF3D0);
	Scr_SetObjectField_t Scr_SetObjectField = Scr_SetObjectField_t(0x4F20F0);
	Scr_GetEntityField_t Scr_GetEntityField = Scr_GetEntityField_t(0x4E8390);
	Scr_SetClientField_t Scr_SetClientField = Scr_SetClientField_t(0x4A6DF0);
	Scr_AddClassField_t Scr_AddClassField = Scr_AddClassField_t(0x4C0E70);

	Scr_ConstructMessageString_t Scr_ConstructMessageString = Scr_ConstructMessageString_t(0x45F940);

	Scr_FreeHudElemConstStrings_t Scr_FreeHudElemConstStrings = Scr_FreeHudElemConstStrings_t(0x5E1120);

	GScr_LoadGameTypeScript_t GScr_LoadGameTypeScript = GScr_LoadGameTypeScript_t(0x4ED9A0);

	GetEntity_t GetEntity = GetEntity_t(0x4BC270);
	GetPlayerEntity_t GetPlayerEntity = GetPlayerEntity_t(0x49C4A0);

	Scr_RegisterFunction_t Scr_RegisterFunction = Scr_RegisterFunction_t(0x492D50);
	Scr_ShutdownAllocNode_t Scr_ShutdownAllocNode = Scr_ShutdownAllocNode_t(0x441650);
	Scr_IsSystemActive_t Scr_IsSystemActive = Scr_IsSystemActive_t(0x4B24E0);

	SL_ConvertToString_t SL_ConvertToString = SL_ConvertToString_t(0x4EC1D0);
	SL_GetString_t SL_GetString = SL_GetString_t(0x4CDC10);
	SL_GetString__t  SL_GetString_ = SL_GetString__t(0x47E310);
	SL_FindString_t SL_FindString = SL_FindString_t(0x434EE0);
	SL_FindLowercaseString_t SL_FindLowercaseString = SL_FindLowercaseString_t(0x4C63E0);
	SL_AddRefToString_t SL_AddRefToString = SL_AddRefToString_t(0x4D9B00);
	SL_RemoveRefToString_t SL_RemoveRefToString = SL_RemoveRefToString_t(0x47CD70);

	ScriptParse_t ScriptParse = ScriptParse_t(0x48A4F0);
	ScriptCompile_t ScriptCompile = ScriptCompile_t(0x426B80);

	scr_const_t* scr_const = reinterpret_cast<scr_const_t*>(0x1AA2E00);

	scrVmPub_t* scrVmPub = reinterpret_cast<scrVmPub_t*>(0x2040CF0);
	scrVarPub_t* scrVarPub = reinterpret_cast<scrVarPub_t*>(0x201A408);
	scrCompilePub_t* scrCompilePub = reinterpret_cast<scrCompilePub_t*>(0x1CDEEC0);
	scrAnimPub_t* scrAnimPub = reinterpret_cast<scrAnimPub_t*>(0x1CDEAA0);

	char* g_EndPos = reinterpret_cast<char*>(0x2045498);
	bool* g_loadedImpureScript = reinterpret_cast<bool*>(0x1DC2208);

	game_hudelem_s* g_hudelems = reinterpret_cast<game_hudelem_s*>(0x18565A8);

	void IncInParam()
	{
		Scr_ClearOutParams();

		if (scrVmPub->top == scrVmPub->maxStack)
		{
			Sys_Error("Internal script stack overflow");
		}

		scrVmPub->top++;
		scrVmPub->inparamcount++;
	}

	void Scr_AddBool(int value)
	{
		assert(value == 0 || value == 1);

		IncInParam();
		scrVmPub->top->type = VAR_INTEGER;
		scrVmPub->top->u.intValue = value;
	}

	void RuntimeErrorInternal(int channel, const char* codePos, unsigned int index, const char* msg)
	{
		static DWORD RuntimeErrorInternal_t = 0x61ABE0;

		__asm
		{
			pushad
			mov eax, msg
			mov edi, channel
			push index
			push codePos
			call RuntimeErrorInternal_t
			add esp, 0x8
			popad
		}
	}

	__declspec(naked) void Scr_NotifyId(unsigned int /*id*/, unsigned __int16 /*stringValue*/, unsigned int /*paramcount*/)
	{
		static DWORD Scr_NotifyId_t = 0x61E670;

		__asm
		{
			pushad

			mov eax, [esp + 0x20 + 0xC] // paramcount
			push [esp + 0x20 + 0x8] // stringValue
			push [esp + 0x20 + 0x8] // id
			call Scr_NotifyId_t
			add esp, 0x8

			popad
			ret
		}
	}
}
