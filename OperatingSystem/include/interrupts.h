#pragma once

namespace interrupts {
	struct interrupt_frame {
		dword ds;                  // Data segment selector
		dword edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
		dword int_no, err_code;    // Interrupt number and error code (if applicable)
		dword eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
	} PACKED;

	namespace exceptions {
		const byte divide_by_zero = 0;
		const byte debug_exception = 1;
		const byte non_maskable_interrupt = 2;
		const byte breakpoint = 3;
		const byte overflow = 4;
		const byte bound_exception = 5;
		const byte invalid_opcode = 6;
		const byte fpu_not_available = 7;
		const byte double_fault = 8;
		const byte coprocessor_segment_overrun = 9;
		const byte invalid_tts = 10;
		const byte segment_not_present = 11;
		const byte stack_exception = 12;
		const byte general_protection = 13;
		const byte page_fault = 14;
		const byte floating_point_error = 16;
		const byte alignment_check = 17;
		const byte machine_check = 18;
	}

	typedef void(*interrupt_handler)(const interrupt_frame& frame);

	void initialize();

	void add_handler(dword interrupt_code, interrupt_handler handler);
}

