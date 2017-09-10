#pragma once

namespace cpu {

	namespace flags {
		const dword carry = 0x1;
		const dword parity = 0x4;
		const dword adjust = 0x10;
		const dword zero = 0x40;
		const dword sign = 0x80;
		const dword trap = 0x100;
		const dword interrupt_enable = 0x200;
		const dword direction = 0x400;
		const dword overflow = 0x800;
		const dword ring_level = 0x1000 | 0x2000;
		const dword ring_level_1 = 0x1000;
		const dword ring_level_2 = 0x2000;
		const dword ring_level_3 = 0x1000 | 0x2000;
		const dword nested_task = 0x4000;
		const dword resume = 1 << 16;
		const dword virtual_8086_mode = 1 << 17;
		const dword alignment_check = 1 << 18;
		const dword virtual_interrupt = 1 << 19;
		const dword virtual_interrupt_pending = 1 << 20;
		const dword id = 1 << 21;
	}
}