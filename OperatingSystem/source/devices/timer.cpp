#include <devices/timer.h>
#include <interrupts.h>

dword system_timer;
timer::on_tick tick_function;

void timer_handler(interrupts::interrupt_frame& frame);
void no_timer_handler(interrupts::interrupt_frame& frame);

void timer::initialize(timer::on_tick f) {
	system_timer = 0;
	tick_function = f;
	interrupts::add_handler(interrupts::irqs::timer, timer_handler);
}

void timer::initialize() {
	system_timer = 0;
	interrupts::add_handler(interrupts::irqs::timer, no_timer_handler);
}

void timer_handler(interrupts::interrupt_frame& frame) {
	system_timer++;
	
	if (system_timer % 18 == 0) {
		tick_function();
	}
}

void no_timer_handler(interrupts::interrupt_frame& frame) {
	system_timer++;
}