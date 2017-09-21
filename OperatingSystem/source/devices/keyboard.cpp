#include <devices/keyboard.h>
#include <interrupts.h>
#include <std/io.h>

using namespace devices;

keyboard::handler _handler;

void keyboard_handler(interrupts::interrupt_frame& frame) {
	byte scan_code;

	scan_code = inb(0x60);

	_handler(scan_code, scan_code & 0x80);
}

void empty_handler(interrupts::interrupt_frame& frame){}

void keyboard::initialize() {
	interrupts::set_handler(interrupts::irqs::keyboard, empty_handler);
}

void keyboard::initialize(keyboard::handler handler) {
	_handler = handler;
	interrupts::set_handler(interrupts::irqs::keyboard, keyboard_handler);
}