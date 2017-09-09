/*
	This entry is called after booting and moving to protected mode
*/
#include <devices/vga.h>
#include <interrupts.h>

GLOBAL void kernel_entry() {
	devices::vga::initialize();
	interrupts::initialize();

	for (int i = 0; i < 100; i++) {
		devices::vga::write_text("hello world");
	}

	while (true) {
		int x = 1 + 1;
	}
}