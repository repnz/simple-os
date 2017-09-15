#include <devices/vga.h>

using namespace devices;

const void* video_memory = (void*)0xb8000;
#define WHITE_ON_BLACK 0x0f
#define DIFF_TO_ASCII ('0' - 0)
#define DIFF_TO_ASCII_HEX ('A' - 0xa)

static byte* current_mem;
static byte current_attributes;

const byte width = 25;
const byte height = 80;
const  int cells = (width * height);

byte screen_row = 0;
byte screen_column = 0;

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
	char value[9];
	value[8] = 0;
	
	int start = 7;

	for (int i = 7; i > 0; --i) {
		value[i] = number % 16;

		if (value[i] >= 0xa) {
			value[i] += DIFF_TO_ASCII_HEX;
		}
		else {
			value[i] += DIFF_TO_ASCII;
		}
		
		number /= 16;

		if (value[i] != '0') {
			start = i;
		}
	}

	write_text(value+start);
}

void vga::write_char(char character) {
	*current_mem++ = character;
	*current_mem++ = current_attributes;
	
	while ((dword)current_mem >= ((dword)video_memory + cells)) {
		current_mem -= cells;
	}
}

void vga::write_text(const char* text) {

	while (*text != 0) {
		write_char(*text);
		++text;
	}
}

void vga::clear() {
	word value = (current_attributes << 8) | ' ';
	word* mem = mem::set<word>((word*)video_memory, value, cells);
	vga::write_text("0x");
	vga::write_hex((dword)mem);
}