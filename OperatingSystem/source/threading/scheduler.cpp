#include <threading/scheduler.h>
#include <interrupts.h>
#include <std/mem.h>
#include <console.h>
#include <cpu.h>

using namespace threading;

#define MAX_THREADS 5
extern dword __threads_stack_start__;



struct thread_state {
	int id; 
	cpu::general_registers regs;
	dword eflags;
	dword eip;
} PACKED;

static thread_state _threads[MAX_THREADS];


thread_state* current_thread_state;
static int _current_length;
static int _next_id;
static dword _next_stack_pointer;
static int _running_thread_index;


static void context_switch(interrupts::interrupt_frame& frame);

void scheduler::initialize() {
	std::mem::zero<thread_state>(_threads, MAX_THREADS);
	_running_thread_index = 0;
	current_thread_state = &_threads[0];

	_next_id = 1;
	_current_length = 1;
	_next_stack_pointer = (dword)&__threads_stack_start__;
	interrupts::set_handler(interrupts::irqs::timer, context_switch);
	console::write_number(_running_thread_index);
	_threads[0].id = 0;
}

void scheduler::create_thread(thread_function f) {
	_threads[_current_length].id = _next_id++;
	_threads[_current_length].regs.ebp = _next_stack_pointer+0x100;
	_threads[_current_length].regs.esp = _next_stack_pointer;
	_threads[_current_length].eip = (dword)f;
	_threads[_current_length].eflags = cpu::get_flags() | cpu::flags::interrupt_enable;
	_next_stack_pointer -= 0x1000;
	++_current_length;
}

void scheduler::thread_exit() {
	std::mem::zero<thread_state>(&_threads[_running_thread_index]);
	
	_current_length -= 1;

	for (int i = _running_thread_index; i < _current_length; ++i) {
		_threads[_running_thread_index] = _threads[_running_thread_index + 1];
	}
}

/*
	This function is called after the IRET of the interrupt handler
	
	- restores the state of the general registers from the thread_state object
	- restores the eflags register
	- sets eip to the current thread

*/


#define DEBUG_CONTEXT_SWITCH

inline static void save_thread_state(const interrupts::interrupt_frame& frame) {
	current_thread_state->regs = frame.regs;
	current_thread_state->eip = frame.eip;
	current_thread_state->eflags = frame.eflags;
}

inline static void find_next_thread() {
	_running_thread_index = (_running_thread_index + 1) % _current_length;
	current_thread_state = &_threads[_running_thread_index];
}

inline static void restore_thread_state(interrupts::interrupt_frame& frame) {
	frame.regs = current_thread_state->regs;
	frame.eip = current_thread_state->eip;
	frame.eflags = current_thread_state->eflags;
}

static void context_switch(interrupts::interrupt_frame& frame) {
	
	save_thread_state(frame);

#ifdef DEBUG_CONTEXT_SWITCH
	console::write_text("now: esp=0x");
	console::write_number(frame.regs.esp, 16);

	console::write_text(" ebp=0x");
	console::write_number(frame.regs.ebp, 16);

	console::write_text(" index=");
	console::write_number(_running_thread_index);
#endif

	find_next_thread();

#ifdef DEBUG_CONTEXT_SWITCH
	console::write_text("   next: esp=0x");
	console::write_number(current_thread_state->regs.esp, 16);

	console::write_text(" ebp=0x");
	console::write_number(current_thread_state->regs.ebp, 16);
	console::write_line();
#endif

	restore_thread_state(frame);
	
}