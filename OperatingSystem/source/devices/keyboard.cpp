#include <devices/keyboard.h>
#include <interrupts.h>
#include <std/io.h>


using devices::keyboard_device;

keyboard_device::handler _handler;

const byte keyboard_port = 0x60;

enum command
{
	set_led = 0xed,
	echo = 0xee,
	scan_code_set_cntrl = 0xf0,
	resend = 0xfe
};

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
byte kbdus[128] =
{
	0, 27,'1','2','3','4','5','6','7','8','9','0','-','=',
	'\b',	/* Backspace */
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


void keyboard_handler(interrupts::interrupt_frame& frame) 
{
	const byte scan_code = inb(keyboard_port);
	
	_handler(kbdus[scan_code & 0x7f], scan_code & 0x80);
}

void empty_handler(interrupts::interrupt_frame& frame){}

void keyboard_device::set_handler(keyboard_device::handler handler)
{
	_handler = handler;
	interrupts::set_handler(interrupts::irqs::keyboard, keyboard_handler);
}

static keyboard_device::result_code wait_for_code(keyboard_device::result_code code) 
{
	byte cur_code = 0;

	for (int i=0; i<10; ++i)
	{
		cur_code = inb(keyboard_port);

		if (cur_code == code) 
		{
			return code;
		}
	}

	return static_cast<keyboard_device::result_code>(cur_code);
}


keyboard_device::result_code keyboard_device::echo_command()
{
	outb_wait(keyboard_port, command::echo);
	return static_cast<result_code>(inb(keyboard_port));
}

byte keyboard_device::get_scan_code_set()
{
	outb(keyboard_port, (byte)command::scan_code_set_cntrl);

	result_code code = wait_for_code(result_code::ack);
	
	if (code != result_code::ack) 
	{
		return -1;
	}

	outb(keyboard_port, 0);

	code = wait_for_code(result_code::ack);

	if (code != result_code::ack) 
	{
		return -1;
	}

	return inb(keyboard_port);
}

keyboard_device::scan_code keyboard_device::wait_for_keypress()
{
	return (scan_code)inb(keyboard_port);
}
