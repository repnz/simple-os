#pragma once

namespace descriptor_tables {
	namespace gdt {
		namespace flags {
			const byte bit_size_32 = 0b01;
			const byte bit_size_16 = 0b00;
			const byte byte_granularity = 0b00;
			const byte page_granularity = 0b10;
		}


		namespace access {
			const byte accessed = 0b00000001;
			const byte not_accessed = 0b00000000;
			const byte rw = 0b00000010;
			const byte grow_down = 0b00000100;
			const byte executable = 0b00001000;
			const byte default_bit = 0b00010000;
			const byte ring_level_0 = 0b00000000;
			const byte ring_level_1 = 0b00100000;
			const byte ring_level_2 = 0b01000000;
			const byte ring_level_3 = 0b01100000;
			const byte present = 0b10000000;
		}

		void set_entry(word offset, dword base, dword limit, byte access, byte flags = flags::bit_size_32 | flags::page_granularity);

		void flush();
	}
}
