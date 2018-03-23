#include <devices/vga.h>
#include <std/mem.h>
#include <std/io.h>
#include <text_mode/cell.h>

using devices::vga_device;

#define VIDEO_MEMORY (text_mode::cell*)0xb8000

/*
 * Calculate the index of a cell location in the video memory
 */
static int calculate_index(byte row, byte column) 
{
	return column + (row * vga_device::width);
}


text_mode::cell* devices::vga_device::address_of(byte row, byte column)
{
	return VIDEO_MEMORY + calculate_index(row, column);
}

void vga_device::set_buffer(text_mode::cell* buffer)
{
	std::mem::copy<text_mode::cell>(
		VIDEO_MEMORY, // dest
		buffer, // src
		vga_device::width * vga_device::height // length
	);
}

void vga_device::set_cursor(byte row, byte column) 
{
	 int buffer_index = calculate_index(row, column);

	outb(0x3D4, 14);
	outb(0x3D5, buffer_index >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, buffer_index);
}