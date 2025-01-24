#pragma once

namespace Components
{
	struct rawMouseValue_t
	{
		int current = 0;
		int previous = 0;

		void ResetDelta();
		int GetDelta() const;
		void Update(int value, bool absolute);
	};

	class RawMouse : public Component
	{
	public:
		RawMouse();

		static void IN_MouseMove();

		static BOOL OnLBDown(LPARAM lParam, WPARAM wParam);
		static BOOL OnLBUp(LPARAM lParam, WPARAM wParam);

		static BOOL OnRBDown(LPARAM lParam, WPARAM wParam);
		static BOOL OnRBUp(LPARAM lParam, WPARAM wParam);

		static BOOL OnMBDown(LPARAM lParam, WPARAM wParam);
		static BOOL OnMBUp(LPARAM lParam, WPARAM wParam);

		static BOOL OnXBDown(LPARAM lParam, WPARAM wParam);
		static BOOL OnXBUp(LPARAM lParam, WPARAM wParam);

	private:
		static Dvar::Var M_RawInput, M_RawInputVerbose, R_FullScreen, R_AutoPriority;
		static rawMouseValue_t MouseRawX, MouseRawY;
		static uint32_t MouseRawEvents;
		static bool InRawInput, FirstRawInputUpdate, InFocus;

		static void IN_ClampMouseMove();
		static void ResetMouseRawEvents();
		static void ProcessMouseRawEvent(DWORD usButtonFlags, DWORD flag_down, DWORD mouse_event);
		static bool GetRawInput(LPARAM lParam, RAWINPUT& raw, UINT& dwSize);
		static BOOL OnRawInput(LPARAM lParam, WPARAM);
		static bool IsMouseInClientBounds();
		static BOOL OnLegacyMouseEvent(UINT Msg, LPARAM lParam, WPARAM wParam);
		static BOOL OnKillFocus(LPARAM lParam, WPARAM);
		static BOOL OnSetFocus(LPARAM lParam, WPARAM);
		static void IN_RawMouseMove();
		static bool ToggleRawInput(bool enable = true);
		static void IN_RawMouse_Init();
		static void IN_Init();
		static void IN_Frame();
		static BOOL IN_ClipCursor();
		static BOOL IN_RecenterMouse();
	};
}
