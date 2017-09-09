#pragma once

namespace descriptor_tables {
	struct descriptor {
		word length;
		void* address;

		descriptor(void* addr, word length) : address(addr), length(length) {
		}
	} PACKED;
}