#pragma once

namespace screen {
	void initialize();
	void write_text(const char* text);
	void write_number(dword number, byte base = 10);
	void write_char(char c);
	void write_line();
	void clear();
}