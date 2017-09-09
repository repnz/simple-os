#pragma once

inline byte inportb(word port) {
	unsigned char rv;
	ASM_VOLATILE("in %0, %1" : "=a" (rv) : "dN" (port));
	return rv;
}

inline void outportb(word port, byte data) {
	ASM_VOLATILE(
	"out %0, %1" : : "dN" (port), "a" (data)
		);
}