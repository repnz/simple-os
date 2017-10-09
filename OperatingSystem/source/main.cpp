
#include <devices/timer.h>
#include <interrupts.h>
#include <memory/memory.h>
#include <console.h>
#include <std/compiler.h>
#include <devices/vga.h>
#include <threading/scheduler.h>
#include <threading/atomic_bool.h>
#include <cpu.h>
#include <devices/keyboard.h>

using namespace devices;


/*
This entry is called after booting and moving to protected mode
*/
GLOBAL void kmain() {

	interrupts::initialize();
	memory::initialize();

	console::initialize();
	console::clear();
	timer::initialize();

	if (keyboard::echo() == keyboard::results::echo) {
		console::write_text("ECHO SCCUESS!\r\n");
	}

	byte set = keyboard::get_scan_code_set();

	console::write_text("0x");
	console::write_number(set, 16);
	console::write_line();


	keyboard::set_scan_code_set(1);

	set = keyboard::get_scan_code_set();

	console::write_text("0x");
	console::write_number(set, 16);
	console::write_line();

	interrupts::enable();

	while (true);
}