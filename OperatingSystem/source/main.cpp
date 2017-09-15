/*
	This entry is called after booting and moving to protected mode
*/
#include <devices/vga.h>
#include <devices/timer.h>
#include <interrupts.h>

void initialize() {
	devices::vga::initialize();
	devices::vga::clear();
	interrupts::initialize();

	timer::initialize();
	interrupts::enable();
}


GLOBAL void kernel_entry() {
	initialize();

	while (true);
}