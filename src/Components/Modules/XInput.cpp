#include "STDInclude.hpp"

#define XINPUT_SENSITIVITY_MULTIPLIER 4 // Arbitrary value I multiply the xinput senstivity dvar with to get nicer values (0-10 range or something)
#define SIGN(d) ((d > 0) - (d < 0))

namespace Components
{
	XINPUT_STATE XInput::xiStates[XUSER_MAX_COUNT];
	XINPUT_STATE XInput::lastXiState = { 0 };
	int XInput::xiPlayerNum = -1;
	std::chrono::milliseconds XInput::timeAtFirstHeldMaxLookX = 0ms; // "For how much time in milliseconds has the player been holding a horizontal direction on their stick, fully" (-1.0 or 1.0)
	bool XInput::isHoldingMaxLookX = false;
	bool XInput::isADS;
	
	Dvar::Var XInput::xpadSensitivity;
	Dvar::Var XInput::xpadEarlyTime;
	Dvar::Var XInput::xpadEarlyMultiplier;
	Dvar::Var XInput::xpadHorizontalMultiplier;
	Dvar::Var XInput::xpadVerticalMultiplier;
	Dvar::Var XInput::xpadAdsMultiplier;

	float XInput::lastMenuNavigationDirection = .0f;
	std::chrono::milliseconds XInput::lastNavigationTime = 0ms;
	std::chrono::milliseconds XInput::msBetweenNavigations = 220ms;

	// This should be read from a text file in the players/ folder, most probably / or from config_mp.cfg
	std::vector<XInput::ActionMapping> mappings = {
		XInput::ActionMapping(XINPUT_GAMEPAD_A, "gostand"),
		XInput::ActionMapping(XINPUT_GAMEPAD_B, "stance"),
		XInput::ActionMapping(XINPUT_GAMEPAD_X, "usereload"),
		XInput::ActionMapping(XINPUT_GAMEPAD_Y, "weapnext", false),
		XInput::ActionMapping(XINPUT_GAMEPAD_LEFT_SHOULDER, "smoke"),
		XInput::ActionMapping(XINPUT_GAMEPAD_RIGHT_SHOULDER, "frag"),
		XInput::ActionMapping(XINPUT_GAMEPAD_LEFT_THUMB,  "breath_sprint"),
		XInput::ActionMapping(XINPUT_GAMEPAD_RIGHT_THUMB, "melee"),
		XInput::ActionMapping(XINPUT_GAMEPAD_START, "togglemenu", false),
		XInput::ActionMapping(XINPUT_GAMEPAD_BACK, "scores"),
		XInput::ActionMapping(XINPUT_GAMEPAD_DPAD_LEFT, "actionslot 3"),
		XInput::ActionMapping(XINPUT_GAMEPAD_DPAD_RIGHT, "actionslot 2"),
		XInput::ActionMapping(XINPUT_GAMEPAD_DPAD_DOWN, "actionslot 1"),
		XInput::ActionMapping(XINPUT_GAMEPAD_DPAD_UP, "actionslot 4"),
	};

	// Same thing
	std::vector<XInput::MenuMapping> menuMappings = {
		XInput::MenuMapping(XINPUT_GAMEPAD_A, Game::keyNum_t::K_KP_ENTER),
		XInput::MenuMapping(XINPUT_GAMEPAD_B, Game::keyNum_t::K_ESCAPE),
		XInput::MenuMapping(XINPUT_GAMEPAD_DPAD_RIGHT, Game::keyNum_t::K_KP_RIGHTARROW),
		XInput::MenuMapping(XINPUT_GAMEPAD_DPAD_LEFT, Game::keyNum_t::K_KP_LEFTARROW),
		XInput::MenuMapping(XINPUT_GAMEPAD_DPAD_UP, Game::keyNum_t::K_KP_UPARROW),
		XInput::MenuMapping(XINPUT_GAMEPAD_DPAD_DOWN, Game::keyNum_t::K_KP_DOWNARROW)
	};

	void XInput::GetLeftStick01Value(XINPUT_STATE* xiState, float& x, float& y) {
		GamepadStickTo01(xiState->Gamepad.sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, x);
		GamepadStickTo01(xiState->Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, y);
	}

	void XInput::GetRightStick01Value(XINPUT_STATE* xiState, float& x, float& y) {
		GamepadStickTo01(xiState->Gamepad.sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, x);
		GamepadStickTo01(xiState->Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, y);
	}

	void XInput::GamepadStickTo01(SHORT value, SHORT deadzone, float& output01) {
		float maxValue = (float)(std::numeric_limits<SHORT>().max() - deadzone);

		output01 = abs(value) > deadzone ? (value - deadzone * SIGN(value)) / maxValue : .0f;

		// log2 allows for a more neat value curve from 0 to 1
		// It is not functional yet, because I suck at maths
		//float test = (log2(abs(output01) + 1.f) - 1.f) * SIGN(value);
	}

	void XInput::Vibrate(int leftVal, int rightVal)
	{
		// Create a Vibraton State
		XINPUT_VIBRATION Vibration;

		// Zeroise the Vibration
		ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

		// Set the Vibration Values
		Vibration.wLeftMotorSpeed = leftVal;
		Vibration.wRightMotorSpeed = rightVal;

		// Vibrate the controller
		XInputSetState(xiPlayerNum, &Vibration);
	}


	void XInput::PollXInputDevices()
	{
		XInput::xiPlayerNum = -1;

		for (int i = XUSER_MAX_COUNT - 1; i >= 0; i--)
		{
			if (XInputGetState(i, &xiStates[i]) == ERROR_SUCCESS)
				XInput::xiPlayerNum = i;
		}
	}

	__declspec(naked) void XInput::CL_FrameStub()
	{
		__asm
		{
			// poll the xinput devices on every client frame
			call XInput::PollXInputDevices

			// execute the code we patched over
			sub     esp, 0Ch
			push    ebx
			push    ebp
			push    esi

			// return back to original code
			push 0x486976
			retn
		}
	}

	void XInput::CL_GamepadMove(int, Game::usercmd_s* cmd)
	{
		if (XInput::xiPlayerNum != -1)
		{
			XINPUT_STATE* xiState = &xiStates[xiPlayerNum];

			// Deadzones
			float moveStickX, moveStickY;
			GetLeftStick01Value(xiState, moveStickX, moveStickY);
			
			if (moveStickX != 0 || moveStickY != 0) {
				// We check for 0:0 again so we don't overwrite keyboard input in case the user doesn't feel like using their gamepad, even though its plugged in
				cmd->rightmove = moveStickX * std::numeric_limits<char>().max();
				cmd->forwardmove = moveStickY * std::numeric_limits<char>().max();
			}

			bool pressingLeftTrigger = xiState->Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
			if (pressingLeftTrigger != XInput::lastXiState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				if (pressingLeftTrigger) {
					Command::Execute("+speed_throw");
					XInput::isADS = true;
				}
				else {
					Command::Execute("-speed_throw");
					XInput::isADS = false;
				}
			}

			bool pressingRightTrigger = xiState->Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
			if (pressingRightTrigger != XInput::lastXiState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				if (pressingRightTrigger) {
					Command::Execute("+attack");
				}
				else {
					Command::Execute("-attack");
				}
			}

			// Buttons (on/off) mappings
			for (size_t i = 0; i < mappings.size(); i++)
			{
				auto mapping = mappings[i];
				auto action = mapping.action;
				auto antiAction = mapping.action;

				if (mapping.isReversible) {
					action = "+" + mapping.action;
					antiAction = "-" + mapping.action;
				}
				else if (mapping.wasPressed) {
					if (xiState->Gamepad.wButtons & mapping.input) {
						// Button still pressed, do not send info
					}
					else {
						mappings[i].wasPressed = false;
					}

					continue;
				}

				if (xiState->Gamepad.wButtons & mapping.input) {
					if (mapping.spamWhenHeld || !mappings[i].wasPressed) {
						Command::Execute(action.c_str());
					}
					mappings[i].wasPressed = true;
				}
				else if (mapping.isReversible && mapping.wasPressed) {
					mappings[i].wasPressed = false;
					Command::Execute(antiAction.c_str());
				}
			}

			memcpy(&XInput::lastXiState, xiState, sizeof XINPUT_STATE);
		}
	}

	__declspec(naked) void XInput::CL_CreateCmdStub()
	{
		__asm
		{
			// do xinput!
			push esi
			push ebp
			call XInput::CL_GamepadMove
			add     esp, 8h

			// execute code we patched over
			add     esp, 4
			fld     st
			pop     ebx

			// return back
			push 0x5A6DBF
			retn
		}
	}

	__declspec(naked) void XInput::MSG_WriteDeltaUsercmdKeyStub()
	{
		__asm
		{
			// fix stack pointer
			add esp, 0Ch

			// put both forward move and rightmove values in the movement button
			mov   dl, byte ptr[edi + 1Ah] // to_forwardMove
			mov   dh, byte ptr[edi + 1Bh] // to_rightMove

			mov[esp + 30h], dx // to_buttons

			mov   dl, byte ptr[ebp + 1Ah] // from_forwardMove
			mov   dh, byte ptr[ebp + 1Bh] // from_rightMove

			mov[esp + 2Ch], dx // from_buttons

			// return back
			push 0x60E40E
			retn
		}
	}

	void XInput::ApplyMovement(Game::msg_t* msg, int key, Game::usercmd_s* from, Game::usercmd_s* to)
	{
		char forward;
		char right;

		if (Game::MSG_ReadBit(msg))
		{
			short movementBits = static_cast<short>(key ^ Game::MSG_ReadBits(msg, 16));

			forward = static_cast<char>(movementBits);
			right = static_cast<char>(movementBits >> 8);
		}
		else
		{
			forward = from->forwardmove;
			right = from->rightmove;
		}

		to->forwardmove = forward;
		to->rightmove = right;
	}

	__declspec(naked) void XInput::MSG_ReadDeltaUsercmdKeyStub()
	{
		__asm
		{
			push ebx // to
			push ebp // from
			push edi // key
			push esi // msg
			call XInput::ApplyMovement
			add     esp, 10h

			// return back
			push 0x4921BF
			ret
		}
	}

	__declspec(naked) void XInput::MSG_ReadDeltaUsercmdKeyStub2()
	{
		__asm
		{
			push ebx // to
			push ebp // from
			push edi // key
			push esi // msg
			call XInput::ApplyMovement
			add     esp, 10h

			// return back
			push 3
			push esi
			push 0x492085
			ret
		}
	}

	void XInput::MenuNavigate() {

		Game::menuDef_t* menuDef = Game::Menu_GetFocused(Game::uiContext);

		if (menuDef) {
			PollXInputDevices();

			if (XInput::xiPlayerNum != -1)
			{
				XINPUT_STATE* xiState = &xiStates[xiPlayerNum];

				// Up/Down
				float moveStickY = abs(xiState->Gamepad.sThumbLY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? xiState->Gamepad.sThumbLY / (float)std::numeric_limits<SHORT>().max() : .0f;

				std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
				std::chrono::milliseconds timeSinceLastNavigation = now - lastNavigationTime;
				bool canNavigate = timeSinceLastNavigation > msBetweenNavigations;

				if (moveStickY > .0f) {
					if (canNavigate || SIGN(moveStickY) != SIGN(lastMenuNavigationDirection)) {
						Game::Menu_SetPrevCursorItem(Game::uiContext, menuDef, 1);
						lastMenuNavigationDirection = moveStickY;
						lastNavigationTime = now;
					}
				}
				else if (moveStickY < .0f) {
					if (canNavigate || SIGN(moveStickY) != SIGN(lastMenuNavigationDirection)) {
						Game::Menu_SetNextCursorItem(Game::uiContext, menuDef, 1);
						lastMenuNavigationDirection = moveStickY;
						lastNavigationTime = now;
					}
				}
				else {
					lastMenuNavigationDirection = .0f;
				}

				for (size_t i = 0; i < menuMappings.size(); i++)
				{
					MenuMapping mapping = menuMappings[i];

					if (mapping.wasPressed) {
						if (xiState->Gamepad.wButtons & mapping.input) {
							// Button still pressed, do not send info
						}
						else {
							menuMappings[i].wasPressed = false;
						}
					}
					else if (xiState->Gamepad.wButtons & mapping.input) {
						Game::UI_KeyEvent(0, mapping.keystroke, 1);
						menuMappings[i].wasPressed = true;
					}
				}
			}
		}
	}

	int XInput::unk_CheckKeyHook(int localClientNum, Game::keyNum_t keyCode) {

		if (XInput::xiPlayerNum != -1)
		{
			XINPUT_STATE* xiState = &xiStates[xiPlayerNum];

			if (keyCode == Game::keyNum_t::K_MOUSE2) {
				bool pressingLeftTrigger = xiState->Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
				if (pressingLeftTrigger != XInput::lastXiState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				{
					if (pressingLeftTrigger) {
						return 1;
					}
					else {
						return 0;
					}
				}
			}
		}

		Utils::Hook::Call<int(int, Game::keyNum_t)>(0x48B2D0)(localClientNum, keyCode);
	}

	void XInput::MouseOverride(Game::clientActive_t* clientActive, float* mx, float* my) {

		XInput::CL_GetMouseMovementCl(clientActive, mx, my);

		if (XInput::xiPlayerNum != -1)
		{
			XINPUT_STATE* xiState = &xiStates[xiPlayerNum];

			float viewSensitivityMultiplier = xpadSensitivity.get<float>() * XINPUT_SENSITIVITY_MULTIPLIER;

			float lockedSensitivityMultiplier = xpadEarlyMultiplier.get<float>();
			float generalXSensitivityMultiplier = xpadHorizontalMultiplier.get<float>();
			float generalYSensitivityMultiplier = xpadVerticalMultiplier.get<float>();
			std::chrono::milliseconds msBeforeUnlockingSensitivity = std::chrono::milliseconds(xpadEarlyTime.get<int>());

			float viewStickX, viewStickY;
			GetRightStick01Value(xiState, viewStickX, viewStickY);

#ifdef DEBUG
			Components::Logger::Print("X:%f \nY:%f\n(holdingMaxX: %d)\n", viewStickX, viewStickY,  XInput::isHoldingMaxLookX);
#endif
			
			// Gamepad horizontal acceleration on view
			if (abs(viewStickX) > 0.80f) {
				if (!XInput::isHoldingMaxLookX) {
					XInput::isHoldingMaxLookX = true;
					XInput::timeAtFirstHeldMaxLookX = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
				}
				else {
					std::chrono::milliseconds hasBeenHoldingLeftXForMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - XInput::timeAtFirstHeldMaxLookX;
#ifdef STEP_SENSITIVITY
					if (hasBeenHoldingLeftXForMs < msBeforeUnlockingSensitivity) {
						viewStickX *= lockedSensitivityMultiplier;
					}
#else
					float coeff = std::clamp(hasBeenHoldingLeftXForMs.count() / (float)msBeforeUnlockingSensitivity.count(), 0.0F, 1.0F);
					viewStickX *= lockedSensitivityMultiplier + coeff * (1.0f - lockedSensitivityMultiplier);
#endif
				}
			}
			else {
				XInput::isHoldingMaxLookX = false;
				XInput::timeAtFirstHeldMaxLookX = 0ms;
				viewStickX *= lockedSensitivityMultiplier;
			}

			float adsMultiplier = 1.0f;

			auto ps = &clientActive->snap.ps;

			// DO NOT use clientActive->usingAds ! It only works for toggle ADS
			if (Game::PM_IsAdsAllowed(ps) && XInput::isADS) {
				adsMultiplier = xpadAdsMultiplier.get<float>();
			}

			if (viewStickX != 0 || viewStickY != 0) {
				*(my) = viewStickX * viewSensitivityMultiplier * generalXSensitivityMultiplier * adsMultiplier;
				*(mx) = -viewStickY * viewSensitivityMultiplier * generalYSensitivityMultiplier * adsMultiplier;
			}

			// Handling killstreaks
			bool pressingRightTrigger = xiState->Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
			if (pressingRightTrigger != XInput::lastXiState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				bool* isInPredator = reinterpret_cast<bool*>(0x8EE3B8);

				if (pressingRightTrigger) {
					Utils::Hook::Set(0xA1C4F4, Game::LOC_SEL_INPUT_CONFIRM);
					if (*isInPredator) {
						// Yea, that's how we boost
						// Command::execute is sync by default so the predator event gets fired properly
						Command::Execute("+attack");
						Command::Execute("-attack");
					}
				}
			}
		}

	}


	// Game -> Client DLL
	__declspec(naked) void CL_GetMouseMovementStub()
	{
		__asm
		{
			push edx;
			push ecx;
			push eax;
			call XInput::MouseOverride;
			add esp, 0xC;
			ret;
		}
	}


	// Client DLL -> Game
	void XInput::CL_GetMouseMovementCl(Game::clientActive_t* result, float* mx, float* my)
	{
		__asm
		{
			push ebx;
			push ecx;
			push edx;
			mov eax, result;
			mov ecx, mx;
			mov edx, my;
			mov ebx, 5A60E0h;
			call ebx;
			pop edx;
			pop ecx;
			pop ebx;
		}
	}

	XInput::XInput()
	{
		// poll xinput devices every client frame
		Utils::Hook(0x486970, XInput::CL_FrameStub, HOOK_JUMP).install()->quick();

		// use the xinput state when creating a usercmd
		Utils::Hook(0x5A6DB9, XInput::CL_CreateCmdStub, HOOK_JUMP).install()->quick();

		// package the forward and right move components in the move buttons
		Utils::Hook(0x60E38D, XInput::MSG_WriteDeltaUsercmdKeyStub, HOOK_JUMP).install()->quick();

		// send two bytes for sending movement data
		Utils::Hook::Set<BYTE>(0x60E501, 16);
		Utils::Hook::Set<BYTE>(0x60E5CD, 16);

		// make sure to parse the movement data properly and apply it
		Utils::Hook(0x492127, XInput::MSG_ReadDeltaUsercmdKeyStub, HOOK_JUMP).install()->quick();
		Utils::Hook(0x492009, XInput::MSG_ReadDeltaUsercmdKeyStub2, HOOK_JUMP).install()->quick();

		Utils::Hook(0x5A617D, CL_GetMouseMovementStub, HOOK_CALL).install()->quick();
		Utils::Hook(0x5A6816, CL_GetMouseMovementStub, HOOK_CALL).install()->quick();
		Utils::Hook(0x5A6829, unk_CheckKeyHook, HOOK_CALL).install()->quick();

		XInput::xpadSensitivity = Dvar::Register<float>("xpad_sensitivity", 1.9f, 0.1f, 10.0f, Game::DVAR_FLAG_SAVED, "View sensitivity for XInput-compatible gamepads");
		XInput::xpadEarlyTime = Dvar::Register<int>("xpad_early_time", 130, 0, 1000, Game::DVAR_FLAG_SAVED, "Time (in milliseconds) of reduced view sensitivity");
		XInput::xpadEarlyMultiplier = Dvar::Register<float>("xpad_early_multiplier", 0.25f, 0.01f, 1.0f, Game::DVAR_FLAG_SAVED, "By how much the view sensitivity is multiplied during xpad_early_time when moving the view stick");
		XInput::xpadHorizontalMultiplier = Dvar::Register<float>("xpad_horizontal_multiplier", 1.5f, 1.0f, 20.0f, Game::DVAR_FLAG_SAVED, "Horizontal view sensitivity multiplier");
		XInput::xpadVerticalMultiplier = Dvar::Register<float>("xpad_vertical_multiplier", 0.8f, 1.0f, 20.0f, Game::DVAR_FLAG_SAVED, "Vertical view sensitivity multiplier");
		XInput::xpadAdsMultiplier = Dvar::Register<float>("xpad_ads_multiplier", 0.7f, 0.1f, 1.0f, Game::DVAR_FLAG_SAVED, "By how much the view sensitivity is multiplied when aiming down the sights.");
		
		PollXInputDevices();

		if (xiPlayerNum >= 0) {
			Vibrate(3000, 3000);
		}

		Scheduler::OnFrame(MenuNavigate);
	}
}
