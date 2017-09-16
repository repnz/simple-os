#include <memory/heap.h>
#include <memory/memory.h>

extern dword __dynamic_memory_start__;
const dword block_size = 14;

memory::heap<5> _heap;

void memory::initialize() {
	_heap.initialize((void*)&__dynamic_memory_start__, block_size);
}

void* memory::allocate(dword bytes) {
	return _heap.allocate(bytes);
}

void memory::free(void* address) {
	_heap.free(address);
}