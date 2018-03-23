#include <devices/timer.h>
#include <interrupts.h>

using devices::timer_device;

dword system_timer;
void(*tick_function)();

const dword ticks_per_second = 18;

static void timer_handler(interrupts::interrupt_frame& frame);
static void no_timer_handler(interrupts::interrupt_frame& frame);

void timer_device::ignore()
{
	interrupts::ignore(interrupts::irqs::timer);
}

void timer_device::set_handler(void(*on_tick)())
{
	system_timer = 0;
	tick_function = on_tick;
	interrupts::set_handler(interrupts::irqs::timer, timer_handler);
}


static void timer_handler(interrupts::interrupt_frame& frame)
{
	system_timer++;
	
	if (system_timer % ticks_per_second == 0)
	{
		tick_function();
	}
}

static void no_timer_handler(interrupts::interrupt_frame& frame)
{
	system_timer++;
}