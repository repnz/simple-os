#include <devices/vga.h>
#include <std/mem.h>
#include <std/compiler.h>

using namespace devices;

#define WHITE_ON_BLACK 0x0f

struct character_cell {
	character_cell(byte attr, char value) : attributes(attr), value(value){
	}

	character_cell(){}

	char value;
	byte attributes;

} PACKED;

const int cells = (vga::width * vga::height);

#define VIDEO_MEMORY (character_cell*)0xb8000
#define VIDEO_MEMORY_END (VIDEO_MEMORY+cells)


static byte current_row;
static byte current_column;

static character_cell default_clear_value;
static bool enable_scrolling;
static byte current_attributes;

void vga::initialize(bool scrolling) {
	enable_scrolling = scrolling;
	current_attributes = WHITE_ON_BLACK;
	default_clear_value = character_cell(current_attributes, ' ');

	current_row = 0;
	current_column = 0;
}

static inline character_cell* calculate_point(byte row, byte column) {
	return VIDEO_MEMORY + (column + (row * vga::width));
}

void vga::scroll_down(byte lines) {

	int scroll_cells = (lines * width);

	std::mem::copy<character_cell>(
		VIDEO_MEMORY,
		VIDEO_MEMORY + scroll_cells,
		(height - lines) * width
		);
	
	std::mem::set<character_cell>(
		VIDEO_MEMORY_END - scroll_cells,
		default_clear_value,
		scroll_cells
		);
}

void vga::scroll_up(byte lines) {
	int scroll_cells = (lines * width);

	std::mem::reverse_copy<character_cell>(
			VIDEO_MEMORY+scroll_cells,
			VIDEO_MEMORY,
			cells - scroll_cells
		);

	std::mem::set<character_cell>(
		VIDEO_MEMORY, 
		default_clear_value,
		scroll_cells
	);
}

inline void write_char_pos(char character, byte attr, byte row, byte column) {
	character_cell* c = calculate_point(row, column);
	c->attributes = attr;
	c->value = character;
}

void vga::write_char(char character) {

	if (current_column >= vga::width) {
		current_column = 0;
		++current_row;
	}

	if (current_row >= vga::height) {
		if (enable_scrolling) {
			current_row = vga::height - 1;
			vga::scroll_down(1);
		}
		else {
			current_row = 0;
		}
	}

	if (character == '\r') {
		current_column = 0;
	}
	else if (character == '\n') {
		++current_row;
	}
	else {

		write_char_pos(character, current_attributes, current_row, current_column);

		++current_column;
	}
}

void vga::write_text(const char* text) {
	while (*text != 0) {
		write_char(*text);
		++text;
	}
}

void vga::clear() {
	std::mem::set<character_cell>(
		VIDEO_MEMORY,
		default_clear_value,
		cells);
} 