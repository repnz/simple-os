#include <threading/scheduler.h>
#include <interrupts.h>
#include <std/mem.h>
#include <cpu.h>

#define DEBUG_SCHEDULER

#ifdef DEBUG_SCHEDULER
#include <text_mode/console.h>
using text_mode::console;
#endif

using namespace threading;

const int max_threads = 5;
const dword stack_memory_per_thread = 0x1000;
extern dword __threads_stack_start__;



struct thread_state 
{
	int id; 
	cpu::general_registers regs;
	dword eflags;
	dword eip;
} PACKED;


static thread_state _threads[max_threads];


thread_state* current_thread_state;
static int _current_length;
static int _next_id;
static dword _next_stack_pointer;
static int _running_thread_index;


static void context_switch(interrupts::interrupt_frame& frame);

void scheduler::initialize() 
{
	std::mem::zero<thread_state>(_threads, max_threads);
	_running_thread_index = -1;
	current_thread_state = &_threads[0];

	_next_id = 1;
	_current_length = 0;
	_next_stack_pointer = (dword)&__threads_stack_start__;
	interrupts::set_handler(interrupts::irqs::timer, context_switch);

	_threads[0].id = 0;
}

void scheduler::create_thread(thread_function start_function) 
{
	_threads[_current_length].id = _next_id++;
	_threads[_current_length].regs.edi = 1;
	_threads[_current_length].regs.esi = 2;
	_threads[_current_length].regs.ebp = 3;
	_threads[_current_length].regs.esp = 4;
	_threads[_current_length].regs.ebx = 5;
	_threads[_current_length].regs.edx = 6;
	_threads[_current_length].regs.ecx = 7;
	_threads[_current_length].regs.eax = 8;
	_threads[_current_length].regs.ebp = _next_stack_pointer;
	_threads[_current_length].regs.esp = _next_stack_pointer;
	_threads[_current_length].eip = (dword)start_function; 
	_threads[_current_length].eflags = cpu::get_flags() | cpu::flags::interrupt_enable;
	
	// stack is growing down
	_next_stack_pointer -= stack_memory_per_thread;
	
	++_current_length;
}

void scheduler::thread_exit() 
{
	std::mem::zero<thread_state>(&_threads[_running_thread_index]);
	
	_current_length -= 1;

	for (int i = _running_thread_index; i < _current_length; ++i) 
	{
		_threads[_running_thread_index] = _threads[_running_thread_index + 1];
	}
}

static void save_thread_state(const interrupts::interrupt_frame& frame) 
{
	current_thread_state->regs = frame.regs;
	// shift the stack position by 20 bytes to compensate for the five DWORD registers (eip, cs, eflags, sp, ss) the CPU put on the stack
	current_thread_state->regs.esp += 20;
	current_thread_state->eip = frame.eip;
	current_thread_state->eflags = frame.eflags;
}

/*
 * Use 'round robin' scheduling
 */
static void find_next_thread() 
{
	_running_thread_index = (_running_thread_index + 1) % _current_length;
	current_thread_state = &_threads[_running_thread_index];
}

/*
* Assembly function that is called when returning from interrupt
* Handles restoring current thread state
*/
extern "C" void restore_thread_state();

/*
- Saves the state of the last thread in the thread_state object
- Finds the next thread to run
- Sets the EIP after the IRET instruction to restore_thread_state
*/
static void context_switch(interrupts::interrupt_frame& frame)
{
	/*
	 * If this is the first context switch, dont save the state
	 */
	if (_running_thread_index != -1)
	{
		save_thread_state(frame);

#ifdef DEBUG_SCHEDULER
		console::write_text("now: esp=0x");
		console::write_number(frame.regs.esp, 16);

		console::write_text(" ebp=0x");
		console::write_number(frame.regs.ebp, 16);

		console::write_text(" index=");
		console::write_number(_running_thread_index);
#endif
	}

	find_next_thread();

#ifdef DEBUG_SCHEDULER
	console::write_text("   next: esp=0x");
	console::write_number(current_thread_state->regs.esp, 16);

	console::write_text(" ebp=0x");
	console::write_number(current_thread_state->regs.ebp, 16);
	console::write_line();
#endif
	
	// set the function that will be called after the IRET
	frame.eip = (dword)restore_thread_state;
}
