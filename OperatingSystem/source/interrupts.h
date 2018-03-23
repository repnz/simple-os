#pragma once
#include <std/compiler.h>
#include <cpu.h>

namespace interrupts 
{
	struct interrupt_frame 
	{
		cpu::general_registers regs;    // Pushed by pusha
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

	namespace irqs {
		const byte timer = 32;
		const byte keyboard = 33;
		const byte cascade_for_8259a = 34;
		const byte serial_port_2 = 35;
		const byte serial_port_1 = 36;
		const byte reserved_37= 37;
		const byte diskette_drive = 38;
		const byte parallel_port_1 = 39;
		const byte cmos_real_time_clock = 40;
		const byte cga_vertical_retrace = 41;
		const byte reserved_42 = 42;
		const byte reserved_43 = 43;
		const byte reserved_44 = 44;
		const byte fpu = 45;
		const byte hard_disk_controller = 46;
		const byte reserved_47 = 47;
	}

	typedef void(*interrupt_handler)(interrupt_frame& frame);

	void initialize();
	
	inline void enable(){
		ASM_VOLATILE("sti");
	}

	inline void disable() {
		ASM_VOLATILE("cli");
	}
	
	void ignore(dword interrupt_code);
	void set_handler(dword interrupt_code, interrupt_handler handler);
}

