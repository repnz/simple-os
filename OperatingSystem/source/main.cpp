#include <devices/timer.h>
#include <interrupts.h>
#include <memory/memory.h>
#include <console.h>
#include <std/compiler.h>
#include <devices/vga.h>

using namespace devices;

void initialize() {
	
	interrupts::initialize();
	memory::initialize();

	console::initialize();
	console::clear(); 

	devices::timer::initialize();

	interrupts::enable();
}

/*
This entry is called after booting and moving to protected mode
*/
GLOBAL void kernel_entry() {
	initialize();

	for (int i = 0; i < vga::height; ++i) {
		console::write_number(i);
		console::write_line();
	}

	vga::scroll_up(2);
}