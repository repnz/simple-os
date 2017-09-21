#include <devices/timer.h>
#include <interrupts.h>
#include <memory/memory.h>
#include <console.h>
#include <std/compiler.h>
#include <devices/vga.h>
#include <threading/scheduler.h>
#include <cpu.h>

using namespace devices;

void thread1();
void thread2();

/*
This entry is called after booting and moving to protected mode
*/
GLOBAL void kernel_entry() {

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

void thread1() {
	while (true){
		console::write_char('A');
	}
}

void thread2() {
	while (true){
		console::write_char('B');
	}
}