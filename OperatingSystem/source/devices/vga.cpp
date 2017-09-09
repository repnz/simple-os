#include <devices/vga.h>

using namespace devices;

const void* video_memory = (void*)0xb8000;
#define WHITE_ON_BLACK 0x0f
#define DIFF_TO_ASCII ('0' - 0)

static byte* current_mem;
static byte current_attributes;

void vga::initialize() {	
	current_mem = (byte*)video_memory;
	current_attributes = WHITE_ON_BLACK;
}

void vga::write_number(dword number) {
	char value[11];
	value[0] = 0;
	value[10] = 0;
	int start = 0;

	for (int i=9; i>=0; --i){
		value[i] = number % 10 + DIFF_TO_ASCII;
		number /= 10;

		if (value[i] != '0') {
			start = i;
		}
	}
	write_text(value + start);
}

void devices::vga::write_hex(dword number) {
	char value[11];
	value[10] = 0;
	
	int start = 0;

	for (dword i = 9; i >= 2; --i) {
		value[i] = number % 16 + DIFF_TO_ASCII;
		number /= 16;

		if (value[i] != '0') {
			start = i;
		}
	}
	
	start -= 2;
	value[start] = '0';
	value[start+1] = 'x';

	write_text(value+start);
}

void vga::write_char(char character) {
	*current_mem++ = character;
	*current_mem++ = current_attributes;
}

void vga::write_text(const char* text) {
	
	while (*text != 0) {
		write_char(*text);
		++text;
	}

}