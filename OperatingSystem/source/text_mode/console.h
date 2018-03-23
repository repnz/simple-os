#pragma once

namespace text_mode
{
	class console 
	{
	public:
		static void initialize();
		static void write_text(const char* text);
		static void write_number(dword number, byte base = 10);
		static void write_char(char character);
		static void write_char(char character, byte attributes);
		static void write_line();

		static void scroll_down(byte lines);
		static void clear();
	};
}
