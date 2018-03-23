#pragma once

namespace devices
{
	class keyboard_device
	{
	public:
		typedef void(*handler)(byte scan_code, bool released);

		enum leds
		{
			scroll_lock = 0,
			number_lock = 1,
			caps_lock = 2
		};

		enum result_code
		{
			resend = 0xFE,
			ack = 0xFA,
			echo = 0xEE,
			error = 0
		};

		enum class scan_code
		{
			NUM_1 = 2, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_0, MIN, EQ, Backspace,
			Tab, q, w, e, r, t, y, u, i, o, p, OpenSq, CloseSq, Enter,
			Ctrl, a, s, d, f, g, h, j, k, l, Semicolon, Apostrophe, GraveAccent, LeftShift,
			Backslash, z, x, c, v, b, n, m, Comma, Dot, Slash, RightShift,
			Asterisk,
			Alt,
			SpaceBar,
			CapsLock,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
			NumLock, ScrollLock, HomeKey, UpArrow, PageUp, NUM_MIN, LeftArrow, Some1, RightArrow, NUM_PLUS,
			End, Down, PageDown, Insert, Delete, Some2, Some3, F11, F12
		};


		static keyboard_device::scan_code wait_for_keypress();

		static void set_handler(handler e);

		static byte get_scan_code_set();

		static result_code echo_command();
	};
}
