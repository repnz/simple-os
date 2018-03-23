#pragma once

namespace descriptor_tables
{
	namespace idt
	{
		const dword size = 255;
		
		namespace attributes 
		{
			const byte present = 0b10000000;
			const byte ring_0 = 0b00000000;
			const byte ring_1 = 0b00100000;
			const byte ring_2 = 0b01000000;
			const byte ring_3 = 0b01100000;
			const byte storage_segment = 0b00000000;
			const byte task_gate_32 = 0b00000101;
			const byte interrupt_gate_16 = 0b00000110;
			const byte interrupt_gate_32 = 0b00001110;
			const byte trap_gate_16 = 0b00000111;
			const byte trap_gate_32 = 0b00001111;

		}

		void set_entry(word code, void* handler, word segment_selector, byte attributes = attributes::interrupt_gate_32);

		void flush();

		void clear();

	}
}
