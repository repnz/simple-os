#pragma once

namespace memory {
	void initialize();

	void* allocate(dword bytes);

	template <typename T>
	T* allocate() {
		return (T*)allocate(sizeof(T));
	}

	template <typename T>
	T* allocate_array(int size) {
		return (T*)allocate(sizeof(T)*size);
	}

	void free(void* address);

}