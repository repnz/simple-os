#pragma once
#include <std/compiler.h>
//#define DEBUG_IO

#ifdef DEBUG_IO 
#include <console.h>
#endif

/* Port 0x80 is used for 'checkpoints' during POST. */
/* The Linux kernel seems to think it is free for use :-/ */
const word wait_port = 0x80;

inline byte inb(word port) {
	byte result;

#ifdef DEBUG_IO 
	console::write_text("inb port=0x");
	console::write_number(port, 16);
#endif
	ASM_VOLATILE("in %0, %1" : "=a" (result) : "dN" (port));

#ifdef DEBUG_IO 
	console::write_text(", result=0x");
	console::write_number(result, 16);
	console::write_line();
#endif

	return result;
}

inline void outb(word port, byte data) {
#ifdef DEBUG_IO 
	console::write_text("outb port=0x");
	console::write_number(port, 16);

	console::write_text(", data=0x");
	console::write_number(data, 16);	

	console::write_line();
#endif

	ASM_VOLATILE(
	"out %0, %1" : : "dN" (port), "a" (data)
		);
}

inline void io_wait(void) {
	outb(wait_port, 0);
}


inline void outb_wait(word port, byte data) {
	outb(port, data);
	io_wait();
}
