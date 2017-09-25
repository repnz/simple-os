#include <devices/timer.h>
#include <interrupts.h>
#include <memory/memory.h>
#include <console.h>
#include <std/compiler.h>
#include <devices/vga.h>
#include <threading/scheduler.h>
#include <threading/atomic_bool.h>
#include <cpu.h>

using namespace devices;

void thread1();
void thread2();

/*
This entry is called after booting and moving to protected mode
*/
GLOBAL void kmain() {

	interrupts::initialize();
	memory::initialize();

	console::initialize();
	console::clear();
	timer::initialize();

	//threading::scheduler::initialize();
	//threading::scheduler::create_thread(thread1);
	//threading::scheduler::create_thread(thread2);

	interrupts::enable();

	while (true){
		console::write_text("hello world");
	}
}

void function(const char* text_to_print) {
	while (true) {
		interrupts::disable();

		console::write_text(text_to_print);
		console::write_text(" is running!!\r\n");
		
		interrupts::enable();
	}
}

void thread1() {
	function(" A ");
}

void thread2() {
	function(" B ");
}