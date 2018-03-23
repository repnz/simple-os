#include <devices/timer.h>
#include <interrupts.h>
#include <memory/memory.h>
#include <text_mode/console.h>
#include <std/compiler.h>
#include <devices/keyboard.h>
#include "threading/scheduler.h"

using text_mode::console;
using devices::keyboard_device;
using devices::timer_device;

void thread1();
void thread2();

/*
This entry is called after booting and moving to protected mode
*/
GLOBAL void kmain() 
{

	interrupts::initialize();
	memory::initialize();

	console::initialize();
	console::clear();
	
	threading::scheduler::initialize();
	threading::scheduler::create_thread(thread1);
	threading::scheduler::create_thread(thread2);

	interrupts::enable();

	while (true);
}

void function(const char* text_to_print) {
	while (true) {
		interrupts::disable();

		console::write_text(text_to_print);
		console::write_text(" is running!!\n");

		interrupts::enable();

		for (int i = 0; i<10000; ++i) {}
	}
}

void thread1() {
	function(" A ");
}

void thread2() {
	function(" B ");
}