/*
	This entry is called after booting and moving to protected mode
*/
#include <devices/vga.h>
#include <interrupts.h>

int real_clock_time;

void empty(interrupts::interrupt_frame& frame) {
	devices::vga::write_char('A');
}

void time(interrupts::interrupt_frame& frame) {
	real_clock_time++;

	if (real_clock_time % 1000) {
		devices::vga::write_number(real_clock_time / 1000);
	}
}

GLOBAL void kernel_entry() {
	real_clock_time = 0;

	devices::vga::initialize();
	interrupts::initialize();
	interrupts::add_handler(interrupts::exceptions::double_fault, time);
	interrupts::add_handler(interrupts::exceptions::general_protection, empty);
	interrupts::enable();

	while (true);
}