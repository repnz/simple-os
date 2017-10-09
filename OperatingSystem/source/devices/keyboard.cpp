#include <devices/keyboard.h>
#include <interrupts.h>
#include <std/io.h>

using namespace devices;

keyboard::handler _handler;

const byte keyboard_port = 0x60;

typedef byte command;

namespace commands {
	const command set_led = 0xed;
	const command echo = 0xee;
	const command scan_code_set_cntrl = 0xF0;
	const command resend = 0xfe;
}

namespace scan_code_set_cntrl_sub  {
	const command get_scan_code_set = 0;
	const command set_scan_code_set_1 = 1;
	const command set_scan_code_set_2 = 2;
	const command set_scan_code_set_3 = 3;
}

struct cmd_result {
	byte cmd;
	byte result;
};

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
byte kbdus[128] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
	0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,					/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};


void keyboard_handler(interrupts::interrupt_frame& frame) {
	byte scan_code;

	scan_code = inb(keyboard_port);

	_handler(kbdus[scan_code & 0x7f], scan_code & 0x80);
}

void empty_handler(interrupts::interrupt_frame& frame){}

void keyboard::initialize() {
	interrupts::set_handler(interrupts::irqs::keyboard, empty_handler);
}

void keyboard::initialize(keyboard::handler handler) {
	_handler = handler;
	interrupts::set_handler(interrupts::irqs::keyboard, keyboard_handler);
}

static inline keyboard::result_code wait_for_code(keyboard::result_code code) {
	keyboard::result_code cur_code;

	for (int i=0; i<10; ++i){
		cur_code = inb(keyboard_port);

		if (cur_code == code) {
			return code;
		}
	}

	return cur_code;
}

keyboard::result_code keyboard::echo() {
	outb_wait(keyboard_port, commands::echo);
	return inb(keyboard_port);
}

keyboard::result_code keyboard::set_rate_and_delay() {
}

byte keyboard::get_scan_code_set() {
	result_code code;

	outb(keyboard_port, commands::scan_code_set_cntrl);

	code = wait_for_code(results::ack);
	
	if (code != results::ack) {
		return code;
	}

	outb(keyboard_port, scan_code_set_cntrl_sub::get_scan_code_set);

	code = wait_for_code(results::ack);

	if (code != results::ack) {
		return code;
	}

	return inb(keyboard_port);
}

keyboard::result_code devices::keyboard::set_scan_code_set(byte set_id)
{
	outb(keyboard_port, commands::scan_code_set_cntrl);

	if (wait_for_code(results::ack) != results::ack) {
		return -1;
	}

	outb(keyboard_port, set_id);

	if (wait_for_code(results::ack) != results::ack) {
		return -1;
	}

	return 0;
}
