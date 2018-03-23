#include <devices/vga.h>
#include <devices/keyboard.h>
#include <std/format.h>
#include <std/mem.h>
#include <text_mode/console.h>
#include <text_mode/cell.h>

using text_mode::console;
using devices::vga_device;
using devices::keyboard_device;

const int number_of_cells = (vga_device::width * vga_device::height);

static byte current_attributes;
static byte current_row;
static byte current_column;

static void keyboard_handler(byte scan_code, bool released);

void console::initialize()
{
	current_attributes = 0xf;
	vga_device::set_cursor(0, 0);
	keyboard_device::set_handler(keyboard_handler);
}

void console::clear()
{
	text_mode::cell* cell_ptr = vga_device::address_of(0, 0);

	// clear the buffer
	std::mem::set<cell>(
		cell_ptr, 
		cell(' ', current_attributes), 
		number_of_cells
		);
}

void console::write_char(char character)
{
	write_char(character, current_attributes);
}


void console::write_char(char character, byte attributes)
{
	if (character == '\n')
	{
		++current_row;
		current_column = 0;
	}
	else
	{
		text_mode::cell* cell = vga_device::address_of(current_row, current_column);

		cell->attributes = attributes;
		cell->character = character;

		++current_column;

		if (current_column >= vga_device::width)
		{
			// fix column value
			current_column = 0;
			current_row++;
		}
	}

	if (current_row >= vga_device::height)
	{
		console::scroll_down(1);
		current_row = vga_device::height - 1;
		current_column = 0;
	}

	vga_device::set_cursor(current_row, current_column);
}

void console::write_text(const char* text)
{
	while (*text != 0) 
	{
		write_char(*text);
		++text;
	}
}

void console::write_number(dword number, byte base)
{
	// buffer for the number
	char buf[32];

	// fill the buffer with reversed number
	int length = std::format::num_to_string_reverse(buf, number, base);

	// print the reversed buffer
	for (int i = length-1; i >= 0; --i)
	{
		write_char(buf[i]);
	}
}

void console::write_line()
{
	write_text("\n");
}

void console::scroll_down(byte lines)
{
	int scroll_cells = (lines * vga_device::width);

	text_mode::cell* video_mem = vga_device::address_of(0, 0);

	// copy upper screen upper
	std::mem::copy<text_mode::cell>(
		video_mem, // dest
		video_mem + scroll_cells, // src
		number_of_cells - scroll_cells // length
		);

	// set lower screen to empty
	std::mem::set<text_mode::cell>(
		video_mem + number_of_cells - scroll_cells, // dest
		cell(' ', current_attributes), // src
		scroll_cells // length
		);
}

static void keyboard_handler(byte scan_code, bool released)
{
	if (!released)
	{
		console::write_char(scan_code);
	}
}