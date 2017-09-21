#include <devices/vga.h>
#include <devices/keyboard.h>
#include <std/format.h>
#include <console.h>

void keyboard_handler(byte scan_code, bool released) {
	if (released) {
		console::write_text("Released!\r\n");
	}
	else {
		console::write_text("Pressed!\r\n");
	}
}

void console::initialize() {
	devices::vga::initialize();
	devices::keyboard::initialize(keyboard_handler);
}

void console::clear() {
	devices::vga::clear();
}

void console::write_char(char c) {
	devices::vga::write_char(c);
}

void console::write_text(const char* text) {
	devices::vga::write_text(text);
}

void console::write_number(dword number, byte base) {
	char buf[32];
	int length = std::format::num_to_string_reverse(buf, number, base);

	for (int i = length-1; i >= 0; --i) {
		devices::vga::write_char(buf[i]);
	}
}

void console::write_line() {
	devices::vga::write_text("\r\n");
}