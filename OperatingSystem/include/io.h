#pragma once

inline byte inb(word port) {
	unsigned char rv;
	ASM_VOLATILE("in %0, %1" : "=a" (rv) : "dN" (port));
	return rv;
}

inline void outb(word port, byte data) {
	ASM_VOLATILE(
	"out %0, %1" : : "dN" (port), "a" (data)
		);
}

inline void io_wait(void) {
	/* Port 0x80 is used for 'checkpoints' during POST. */
	/* The Linux kernel seems to think it is free for use :-/ */
	outb(0x80, 0);
}