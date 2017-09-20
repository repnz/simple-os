#include <devices/vga.h>
#include <std/mem.h>

using namespace devices;

const void* video_memory = (void*)0xb8000;

static byte* current_mem;
static byte current_attributes;
#define WHITE_ON_BLACK 0x0f

const byte width = 80;
const byte height = 25;
const  int cells = (width * height);

byte row = 0;
byte column = 0;

static inline byte* calculate_point() {
	return (byte*)video_memory + ((column + (row * width)) * 2);
}

static bool increase_row() {
	row++;

	if (row >= height) {
		row = 0;
	}
}

static bool increase_column() {
	column++;

	if (column >= width) {
		column = 0;
		increase_row();
		current_mem = calculate_point();
	}
}

void vga::initialize() {	
	current_mem = (byte*)video_memory;
	current_attributes = WHITE_ON_BLACK;
	row = 0;
	column = 0;
}

void vga::write_char(char character) {
	if (character == '\r') {
		column = 0;
		current_mem = calculate_point();
	}
	else if (character == '\n') {
		increase_row();
		current_mem = calculate_point();
	}
	else {
		*current_mem++ = character;
		*current_mem++ = current_attributes;

		increase_column();
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
	std::mem::set<word>((word*)video_memory, value, cells);
}