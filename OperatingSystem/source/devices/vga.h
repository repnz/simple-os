#pragma once 
#include <text_mode/cell.h>

namespace devices 
{
	class vga_device
	{
	public:
		static const byte width = 80;
		static const byte height = 25;

		static text_mode::cell* address_of(byte row, byte column);

		static void set_buffer(text_mode::cell* buffer);

		static void set_cursor(byte row, byte column);
	};
}
