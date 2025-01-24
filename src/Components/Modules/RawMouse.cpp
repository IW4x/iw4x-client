#include "Gamepad.hpp"
#include "RawMouse.hpp"
#include "Window.hpp"

namespace Components
{
	void rawMouseValue_t::ResetDelta()
	{
		this->previous = this->current;
	}

	int rawMouseValue_t::GetDelta() const
	{
		return this->current - this->previous;
	}

	void rawMouseValue_t::Update(int value, bool absolute)
	{
		if (absolute) // if mouse is absolute, reset current value
			this->current = 0;

		this->current += value;
	}

	Dvar::Var RawMouse::M_RawInput;
	Dvar::Var RawMouse::M_RawInputVerbose;
	Dvar::Var RawMouse::R_AutoPriority = nullptr;
	Dvar::Var RawMouse::R_FullScreen = nullptr;

	rawMouseValue_t RawMouse::MouseRawX{ 0,0 };
	rawMouseValue_t RawMouse::MouseRawY{ 0,0 };
	uint32_t RawMouse::MouseRawEvents = 0;

	bool RawMouse::InRawInput = false;
	bool RawMouse::InFocus = false;
	bool RawMouse::FirstRawInputUpdate = true;

	constexpr const int K_MWHEELUP = 205;
	constexpr const int K_MWHEELDOWN = 206;

	void ClampMousePos(POINT& curPos)
	{
		tagRECT rc;
		if (GetWindowRect(Window::GetWindow(), &rc) != TRUE)
			return;
		auto isClamped = false;
		if (curPos.x >= rc.left)
		{
			if (curPos.x >= rc.right)
			{
				curPos.x = rc.right - 1;
				isClamped = true;
			}
		}
		else
		{
			curPos.x = rc.left;
			isClamped = true;
		}

		if (curPos.y >= rc.top)
		{
			if (curPos.y >= rc.bottom)
			{
				curPos.y = rc.bottom - 1;
				isClamped = true;
			}
		}
		else
		{
			curPos.y = rc.top;
			isClamped = true;
		}

		if (isClamped)
		{
			SetCursorPos(curPos.x, curPos.y);
		}
	}

	void RawMouse::IN_ClampMouseMove()
	{
		tagPOINT curPos;
		GetCursorPos(&curPos);
		ClampMousePos(curPos);
	}

	bool CheckButtonFlag(DWORD usButtonFlags, DWORD flag)
	{
		return (usButtonFlags & flag) != 0u;
	}

	void RawMouse::ResetMouseRawEvents()
	{
		// this code messes up sometimes and forces attack in alt-tabbing.
		//if (MouseRawEvents != 0)
		//{
		//	// send release event for all buttons.
		//	Game::IN_MouseEvent(MouseRawEvents);
		//
		//	if (M_RawInputVerbose.get<bool>())
		//		Logger::Debug("Force-Releasing buttons {}", MouseRawEvents);
		//}
		MouseRawEvents = 0u;
		FirstRawInputUpdate = true;
	}

	void RawMouse::ProcessMouseRawEvent(DWORD usButtonFlags, DWORD flagDown, DWORD mouseEvent)
	{
		const uint32_t prevMouseEvents = MouseRawEvents;

		if (CheckButtonFlag(usButtonFlags, flagDown))
		{
			if (M_RawInputVerbose.get<bool>())
			{
				if ((prevMouseEvents & mouseEvent) != 0u)
					Logger::Debug("!! Pressing button that wasn't released");

				Logger::Debug("Mouse button down: [{}, {}]", mouseEvent, prevMouseEvents);
			}

			MouseRawEvents |= mouseEvent;
		}

		if (CheckButtonFlag(usButtonFlags, flagDown << 1u))
		{
			// Sometimes when alt-tabbing LMB release somehow gets passed there,
			// releasing button that was not even pressed...
			if ((prevMouseEvents & mouseEvent) == 0u)
			{
				if (M_RawInputVerbose.get<bool>())
					Logger::Debug("!! Releasing button that wasn't pressed");

				return;
			}

			if (M_RawInputVerbose.get<bool>())
				Logger::Debug("Mouse button up: [{}, {}]", mouseEvent, prevMouseEvents);

			MouseRawEvents &= ~mouseEvent;
		}
	}

	bool RawMouse::GetRawInput(LPARAM lParam, RAWINPUT& raw, UINT& dwSize)
	{
		const UINT result = GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, &raw, &dwSize, sizeof(RAWINPUTHEADER));

		if (result == static_cast<UINT>(-1) || raw.header.dwType != RIM_TYPEMOUSE)
			return false;

		return true;
	}

	BOOL RawMouse::OnRawInput(LPARAM lParam, WPARAM)
	{
		if (!InRawInput) {
			ResetMouseRawEvents();
			return TRUE;
		}

		UINT dwSize = sizeof(RAWINPUT);
		static RAWINPUT raw;

		if (!GetRawInput(lParam, raw, dwSize))
			return TRUE;

		if (!RawMouse::InFocus)
			return TRUE;

		// Is there's really absolute mouse on earth?
		const bool bAbsMouseMove = (raw.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) != 0u;

		MouseRawX.Update(raw.data.mouse.lLastX, bAbsMouseMove);
		MouseRawY.Update(raw.data.mouse.lLastY, bAbsMouseMove);

		// fix of angle snap when alt tabbing.
		if (FirstRawInputUpdate)
		{
			MouseRawX.ResetDelta();
			MouseRawY.ResetDelta();
			FirstRawInputUpdate = false;
		}

		// Process mouse buttons events
		// format: (current_rawinput_flags, rawinput_mouse_button_keycode, cod_mouse_event).
		// The function checks both down & up states.
		ProcessMouseRawEvent(raw.data.mouse.usButtonFlags, RI_MOUSE_BUTTON_1_DOWN, 1);
		ProcessMouseRawEvent(raw.data.mouse.usButtonFlags, RI_MOUSE_BUTTON_2_DOWN, 2);
		ProcessMouseRawEvent(raw.data.mouse.usButtonFlags, RI_MOUSE_BUTTON_3_DOWN, 4);
		ProcessMouseRawEvent(raw.data.mouse.usButtonFlags, RI_MOUSE_BUTTON_4_DOWN, 8);
		ProcessMouseRawEvent(raw.data.mouse.usButtonFlags, RI_MOUSE_BUTTON_5_DOWN, 16);

		Game::IN_MouseEvent(MouseRawEvents);

		if (raw.data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
		{
			const SHORT scroll_delta = static_cast<SHORT>(raw.data.mouse.usButtonData);

			if (scroll_delta > 0)
				Game::Sys_QueEvents(Game::g_wv->sysMsgTime, 1, K_MWHEELDOWN, 0, 0);
			if (scroll_delta < 0)
				Game::Sys_QueEvents(Game::g_wv->sysMsgTime, 1, K_MWHEELUP, 0, 0);
		}

		return TRUE;
	}

	bool RawMouse::IsMouseInClientBounds()
	{
		POINT curPos;
		GetCursorPos(&curPos);
		ScreenToClient(Window::GetWindow(), &curPos);

		RECT rect;
		Window::Dimension(Window::GetWindow(), &rect);

		return (curPos.y >= 0 && curPos.x >= 0 && (rect.right - rect.left) >= curPos.x && (rect.bottom - rect.top) >= curPos.y);
	}

	BOOL RawMouse::OnLegacyMouseEvent(UINT Msg, LPARAM lParam, WPARAM wParam)
	{
		int MouseEvents = (wParam & MK_LBUTTON) != 0;
		if ((wParam & MK_RBUTTON) != 0)
			MouseEvents |= 2u;
		if ((wParam & MK_MBUTTON) != 0)
			MouseEvents |= 4u;
		if ((wParam & MK_XBUTTON1) != 0)
			MouseEvents |= 8u;
		if ((wParam & MK_XBUTTON2) != 0)
			MouseEvents |= 0x10u;

		if (M_RawInput.get<bool>())
		{
			if (MouseEvents == 0 || !RawMouse::InFocus)
				return FALSE;

			if (M_RawInputVerbose.get<bool>())
				Logger::Debug("Window Mouse Message: [{}, {}]", MouseEvents, MouseRawEvents);

			MouseRawEvents = MouseEvents;
		}

		Game::IN_MouseEvent(MouseEvents);

		// we should call DefWindowProcA there as game, thats why there is 8 1line functions...
		return DefWindowProcA(Window::GetWindow(), Msg, wParam, lParam);
	}

	BOOL RawMouse::OnKillFocus([[maybe_unused]] LPARAM lParam, WPARAM)
	{
		RawMouse::InFocus = false;

		ToggleRawInput(false);
		ResetMouseRawEvents();

		if (!R_AutoPriority.get<Game::dvar_t*>() || !R_AutoPriority.get<bool>())
			return DefWindowProc(Window::GetWindow(), WM_KILLFOCUS, 0, 0);

		SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
		return FALSE;
	}

	BOOL RawMouse::OnSetFocus([[maybe_unused]] LPARAM lParam, WPARAM)
	{
		RawMouse::InFocus = true;

		if (!R_AutoPriority.get<Game::dvar_t*>() || !R_AutoPriority.get<bool>())
			return DefWindowProc(Window::GetWindow(), WM_KILLFOCUS, 0, 0);

		SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
		return FALSE;
	}

	void RawMouse::IN_RawMouseMove()
	{
		auto dx = MouseRawX.GetDelta();
		auto dy = MouseRawY.GetDelta();

		MouseRawX.ResetDelta();
		MouseRawY.ResetDelta();

		// Don't use raw input for menu?
		// Because it needs to call the ScreenToClient
		tagPOINT curPos;
		GetCursorPos(&curPos);
		Game::s_wmv->oldPos = curPos;
		ScreenToClient(Window::GetWindow(), &curPos);

		Gamepad::OnMouseMove(curPos.x, curPos.y, dx, dy);

		// CL_MouseEvent returns true if we need to recenter mouse (the same case when we need clipping)
		if (!Game::CL_MouseEvent(curPos.x, curPos.y, dx, dy))
		{
			ClipCursor(NULL);
			return;
		}

		RECT Rect;
		if (GetWindowRect(Window::GetWindow(), &Rect) == TRUE)
		{
			RawMouse::IN_RecenterMouse();
		}
	}

	bool RawMouse::ToggleRawInput(bool enable)
	{
		if (!M_RawInput.get<bool>())
		{
			if (!InRawInput)
				return false;

			enable = false;
		}
		else
		{
			if (InRawInput == enable)
				return InRawInput;
		}

		constexpr DWORD rawMouseFlags = RIDEV_INPUTSINK | RIDEV_NOLEGACY;

		RAWINPUTDEVICE Rid[1];
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = (enable ? rawMouseFlags : RIDEV_REMOVE);
		Rid[0].hwndTarget = enable ? Window::GetWindow() : NULL;

		bool success = RegisterRawInputDevices(Rid, ARRAYSIZE(Rid), sizeof(Rid[0])) == TRUE;

		if (!success)
			Logger::Warning(Game::CON_CHANNEL_SYSTEM, "RawInputDevices: failed: {}\n", GetLastError());
		else
		{
			InRawInput = (Rid[0].dwFlags & RIDEV_REMOVE) == 0u;

			if (M_RawInputVerbose.get<bool>())
			{
				if (InRawInput)
					Logger::Debug("Raw Input enabled");
				else
					Logger::Debug("Raw Input disabled");
			}

			if (!InRawInput)
				ResetMouseRawEvents();
		}

		return true;
	}

	void RawMouse::IN_RawMouse_Init()
	{
		if (Window::GetWindow() && ToggleRawInput(true)) {
			Logger::Debug("Raw Mouse Init");
		}

	}

	void RawMouse::IN_Init()
	{
		Game::IN_Init();
		IN_RawMouse_Init();
		ResetMouseRawEvents();

		R_AutoPriority = Dvar::Var("r_autopriority");
		R_FullScreen = Dvar::Var(0x069F0DA0);

#if true
		// https://github.com/iw4x/iw4x-client/issues/177
		M_RawInput.set(false);
#endif

	}

	void RawMouse::IN_Frame()
	{
		if (RawMouse::InFocus)
			ToggleRawInput(IsMouseInClientBounds());

		return Game::IN_Frame();
	}

	BOOL RawMouse::IN_ClipCursor()
	{
		RECT clientRect;
		if (!GetClientRect(Window::GetWindow(), &clientRect))
		{
			return FALSE;
		}

		ClientToScreen(Window::GetWindow(), std::bit_cast<POINT*>(&clientRect.left));
		ClientToScreen(Window::GetWindow(), std::bit_cast<POINT*>(&clientRect.right));
		return ClipCursor(&clientRect);
	}

	BOOL RawMouse::IN_RecenterMouse()
	{
		IN_ClipCursor();
		return Game::IN_RecenterMouse();
	}

	void RawMouse::IN_MouseMove()
	{
		if (!RawMouse::InFocus)
		{
			ClipCursor(NULL);
			return;
		}

		if (InRawInput)
		{
			return IN_RawMouseMove();
		}

		// IN_MouseMove
		if (GetForegroundWindow() != Window::GetWindow())
			return;

		tagPOINT cursorPos;
		static tagPOINT prevCursorPos;

		GetCursorPos(&cursorPos);
		if (R_FullScreen.get<Game::dvar_t*>() && R_FullScreen.get<bool>())
			ClampMousePos(cursorPos);

		int deltaX = cursorPos.x - prevCursorPos.x;
		int deltaY = cursorPos.y - prevCursorPos.y;
		prevCursorPos = cursorPos;

		ScreenToClient(Window::GetWindow(), &cursorPos);
		auto recenterMouse = Game::CL_MouseEvent(cursorPos.x, cursorPos.y, deltaX, deltaY);

		if (recenterMouse && (deltaX || deltaY))
		{
			RECT Rect;
			if (GetWindowRect(Window::GetWindow(), &Rect) == TRUE)
			{
				RawMouse::IN_ClipCursor();

				int WindowCenterX = (Rect.right + Rect.left) / 2;
				int WindowCenterY = (Rect.top + Rect.bottom) / 2;
				SetCursorPos(WindowCenterX, WindowCenterY);

				prevCursorPos.x = WindowCenterX;
				prevCursorPos.y = WindowCenterY;
			}
		}
		else if (!recenterMouse)
		{
			ClipCursor(NULL);
		}
	}

	BOOL RawMouse::OnLBDown(LPARAM lParam, WPARAM wParam)
	{
		return OnLegacyMouseEvent(WM_LBUTTONDOWN, lParam, wParam);
	}

	BOOL RawMouse::OnLBUp(LPARAM lParam, WPARAM wParam)
	{
		return OnLegacyMouseEvent(WM_LBUTTONUP, lParam, wParam);
	}

	BOOL RawMouse::OnRBDown(LPARAM lParam, WPARAM wParam)
	{
		return OnLegacyMouseEvent(WM_RBUTTONDOWN, lParam, wParam);
	}

	BOOL RawMouse::OnRBUp(LPARAM lParam, WPARAM wParam)
	{
		return OnLegacyMouseEvent(WM_RBUTTONUP, lParam, wParam);
	}

	BOOL RawMouse::OnMBDown(LPARAM lParam, WPARAM wParam)
	{
		return OnLegacyMouseEvent(WM_MBUTTONDOWN, lParam, wParam);
	}

	BOOL RawMouse::OnMBUp(LPARAM lParam, WPARAM wParam)
	{
		return OnLegacyMouseEvent(WM_MBUTTONUP, lParam, wParam);
	}

	BOOL RawMouse::OnXBDown(LPARAM lParam, WPARAM wParam)
	{
		return OnLegacyMouseEvent(WM_XBUTTONDOWN, lParam, wParam);
	}

	BOOL RawMouse::OnXBUp(LPARAM lParam, WPARAM wParam)
	{
		return OnLegacyMouseEvent(WM_XBUTTONUP, lParam, wParam);
	}

	RawMouse::RawMouse()
	{
		Utils::Hook(0x475E65, IN_MouseMove, HOOK_JUMP).install()->quick();
		Utils::Hook(0x475E8D, IN_MouseMove, HOOK_JUMP).install()->quick();
		//Utils::Hook(0x475E9E, IN_MouseMove, HOOK_JUMP).install()->quick(); // Used in controller

		Utils::Hook(0x467C03, IN_Init, HOOK_CALL).install()->quick();
		Utils::Hook(0x64D095, IN_Init, HOOK_JUMP).install()->quick();

		Utils::Hook(0x60BFB9, IN_Frame, HOOK_CALL).install()->quick();
		Utils::Hook(0x4A87E2, IN_Frame, HOOK_CALL).install()->quick();
		Utils::Hook(0x48A0E6, IN_Frame, HOOK_CALL).install()->quick();

		Utils::Hook(0x473517, IN_RecenterMouse, HOOK_CALL).install()->quick();
		M_RawInput = Dvar::Register<bool>("m_rawinput", true, Game::DVAR_ARCHIVE, "Use raw mouse input, Improves accuracy & has better support for higher polling rates");
		M_RawInputVerbose = Dvar::Register<bool>("m_rawinput_verbose", false, Game::DVAR_ARCHIVE | Game::DVAR_SAVED, "Raw mouse input debug log");

		Window::OnWndMessage(WM_KILLFOCUS, OnKillFocus);
		Window::OnWndMessage(WM_SETFOCUS, OnSetFocus);

		// not the cleanest way but we got Msg in arguments now...
		Window::OnWndMessage(WM_LBUTTONDOWN, OnLBDown);
		Window::OnWndMessage(WM_LBUTTONUP, OnLBUp);
		Window::OnWndMessage(WM_RBUTTONDOWN, OnRBDown);
		Window::OnWndMessage(WM_RBUTTONUP, OnRBUp);
		Window::OnWndMessage(WM_MBUTTONDOWN, OnMBDown);
		Window::OnWndMessage(WM_MBUTTONUP, OnMBUp);
		Window::OnWndMessage(WM_XBUTTONDOWN, OnXBDown);
		Window::OnWndMessage(WM_XBUTTONUP, OnXBUp);

		Window::OnWndMessage(WM_INPUT, OnRawInput);
		Window::OnCreate(IN_RawMouse_Init);
	}
}
