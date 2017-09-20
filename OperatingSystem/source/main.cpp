#include <devices/timer.h>
#include <interrupts.h>
#include <memory/memory.h>
#include <screen.h>
#include <std/compiler.h>

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

	my_struct* s;

	s = memory::allocate_array<my_struct>(10);
	
	my_struct* ptr = s;

	for (int i = 0; i < 10; ++i) {
		s->a = 0x41414141;
		s->b = 0x42424242;
		s->c = 0x43434343;
		++ptr;
	}

	my_struct* other = memory::allocate<my_struct>();
	other->a = 10;
	other->b = 10;
	other->c = 10;

	memory::free(s);

	while (true);
}