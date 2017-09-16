#include <devices/timer.h>
#include <interrupts.h>
#include <memory/memory.h>
#include <format.h>
#include <screen.h>

void initialize() {
	screen::initialize();
	screen::clear(); 

	interrupts::initialize();
	memory::initialize();

	timer::initialize();
	interrupts::enable();
}

struct my_struct {
	int a;
	int b;
	int c;
};

/*
This entry is called after booting and moving to protected mode
*/
GLOBAL void kernel_entry() {
	initialize();

	for (int i=0; i<5; ++i){
		my_struct* s = memory::allocate<my_struct>();
		memory::free(s);
	}


	while (true);
}