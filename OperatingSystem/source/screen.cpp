#include <screen.h>
#include <devices/vga.h>
#include <format.h>

#define WHITE_ON_BLACK 0x0f

void screen::initialize() {
	devices::vga::initialize();
}

void screen::clear() {
	devices::vga::clear();
}

void screen::write_char(char c) {
	devices::vga::write_char(c);
}

void screen::write_text(const char* text) {
	devices::vga::write_text(text);
}

void screen::write_number(dword number, byte base) {
	char buf[32];
	int length = format::num_to_string_reverse(buf, number, base);

	for (int i = length-1; i >= 0; --i) {
		devices::vga::write_char(buf[i]);
	}
}