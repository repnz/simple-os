#pragma once 

namespace devices {
	namespace vga {
		void initialize();
		void write_char(char character);
		void write_number(dword value);
		void write_hex(dword value);
		void write_text(const char* text);
		void clear();
	}
}
