#pragma once 

namespace devices {
	namespace vga {
		const byte width = 80;
		const byte height = 25;

		void initialize(bool enable_scrolling = true);
		void write_char(char character);
		void write_text(const char* text);
		void scroll_down(byte lines);
		void clear();
	}
}
