#pragma once

namespace Components
{
	class XInput : public Component
	{
	public:
		XInput();

		struct ActionMapping {
			int input;
			std::string action;
			bool isReversible;
			bool wasPressed = false;
			bool spamWhenHeld = false;

			ActionMapping(int input, std::string action, bool isReversible = true, bool spamWhenHeld = false)
			{
				this->action = action;
				this->isReversible = isReversible;
				this->input = input;
				this->spamWhenHeld = spamWhenHeld;
			}
		};

		struct MenuMapping {
			int input;
			Game::keyNum_t keystroke;
			bool wasPressed = false;

			MenuMapping(int input, Game::keyNum_t keystroke)
			{
				this->keystroke = keystroke;
				this->input = input;
			}
		};

	private:
		static XINPUT_STATE xiStates[XUSER_MAX_COUNT];
		static int xiPlayerNum;
		static XINPUT_STATE lastXiState;

		static bool isHoldingMaxLookX;
		static std::chrono::milliseconds timeAtFirstHeldMaxLookX;
		static bool isADS;

		static std::chrono::milliseconds lastNavigationTime;
		static std::chrono::milliseconds msBetweenNavigations;
		static float lastMenuNavigationDirection;

		static Dvar::Var XInput::xpadSensitivity;
		static Dvar::Var XInput::xpadEarlyTime;
		static Dvar::Var XInput::xpadEarlyMultiplier;
		static Dvar::Var XInput::xpadHorizontalMultiplier;
		static Dvar::Var XInput::xpadVerticalMultiplier;
		static Dvar::Var XInput::xpadAdsMultiplier;

		static void CL_GetMouseMovementCl(Game::clientActive_t* result, float* mx, float* my);
		static int unk_CheckKeyHook(int localClientNum, Game::keyNum_t keyCode);

		static void MouseOverride(Game::clientActive_t* clientActive, float* my, float* mx);
		static void Vibrate(int leftVal = 0, int rightVal = 0);

		static void CL_FrameStub();
		static void PollXInputDevices();

		static void CL_CreateCmdStub();
		static void CL_GamepadMove(int, Game::usercmd_s*);
		static void MenuNavigate();

		static void MSG_WriteDeltaUsercmdKeyStub();

		static void ApplyMovement(Game::msg_t* msg, int key, Game::usercmd_s* from, Game::usercmd_s* to);

		static void MSG_ReadDeltaUsercmdKeyStub();
		static void MSG_ReadDeltaUsercmdKeyStub2();

		static void GetLeftStick01Value(XINPUT_STATE* xiState, float& x, float& y);
		static void GetRightStick01Value(XINPUT_STATE* xiState, float& x, float& y);
		static void GamepadStickTo01(SHORT value, SHORT deadzone, float& output01);
	};
}
