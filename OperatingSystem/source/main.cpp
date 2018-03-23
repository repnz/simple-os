#include <devices/timer.h>
#include <interrupts.h>
#include <memory/memory.h>
#include <text_mode/console.h>
#include <std/compiler.h>
#include <devices/keyboard.h>

using text_mode::console;

using devices::keyboard_device;
using devices::timer_device;

/*
This entry is called after booting and moving to protected mode
*/
GLOBAL void kmain() 
{

	interrupts::initialize();
	memory::initialize();

	console::initialize();
	console::clear();
	timer_device::ignore();
	
	for (int i=0; i<75; ++i)
	{
		for (char c = 'a'; c<='z'; ++c)
		{
			console::write_char(c);
		}
	}

	for (int i=0; i<2; ++i)
	{
		for (char c = 'a'; c <= 'z'; ++c)
		{
			console::write_char(c);
		}
	}
	
	interrupts::enable();

	while (true);
}