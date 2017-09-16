#pragma once

namespace memory {
	void initialize();

	void* allocate(dword bytes);

	template <typename T>
	T* allocate() {
		return (T*)allocate(sizeof(T));
	}

	void free(void* address);

}