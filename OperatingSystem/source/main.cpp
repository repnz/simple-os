/*
	This entry is called after booting and moving to protected mode
*/
#include <devices/vga.h>
#include <devices/timer.h>
#include <interrupts.h>

void print_hello_world() {
	devices::vga::write_text("hello world ");
}

GLOBAL void kernel_entry() {

	devices::vga::initialize();
	interrupts::initialize();
	timer::initialize(print_hello_world);

	interrupts::enable();

	while (true);
}