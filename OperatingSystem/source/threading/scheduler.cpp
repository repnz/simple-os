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
	interrupts::interrupt_frame frame;
};

thread_state _threads[MAX_THREADS];

int _current_length;
int _index;
int _next_id;
dword _next_stack_pointer;

void context_switch(interrupts::interrupt_frame& frame);

void scheduler::initialize() {
	std::mem::zero<thread_state>(_threads, MAX_THREADS);
	_index = 0;
	_next_id = 1;
	_current_length = 1;
	_next_stack_pointer = (dword)&__threads_stack_start__;
	interrupts::set_handler(interrupts::irqs::timer, context_switch);
	console::write_number(_index);
	_threads[0].id = 0;
}

void scheduler::create_thread(thread_function f) {
	_threads[_current_length].id = _next_id++;
	_threads[_current_length].frame.eip = (dword)f;
	_threads[_current_length].frame.ebp = _next_stack_pointer;
	_threads[_current_length].frame.esp = _next_stack_pointer;
	_threads[_current_length].frame.ds = 0x10;
	_threads[_current_length].frame.ss = 0x10;
	_threads[_current_length].frame.cs = 0x8;
	_threads[_current_length].frame.eflags = cpu::get_flags() | cpu::flags::interrupt_enable;
	_next_stack_pointer -= 0x1000;
	++_current_length;
}

void scheduler::thread_exit() {
	interrupts::disable();
	std::mem::zero<thread_state>(&_threads[_index]);
	
	_current_length -= 1;

	for (int i = _index; i < _current_length; ++i) {
		_threads[_index] = _threads[_index + 1];
	}

	interrupts::enable();
}

void context_switch(interrupts::interrupt_frame& frame) {
	_threads[_index].frame = frame;
	_index = (_index + 1) % _current_length;
	console::write_number(_index);
	frame = _threads[_index].frame;
}