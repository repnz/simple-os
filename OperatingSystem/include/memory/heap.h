#pragma once

namespace memory {

	const int entries_size = 20;

	class heap {
	private:
		void* _start;
		int _block_size;
		int _current_index;
		bool _entries[entries_size];

		int search_free_index(int start_search, int end_search, int num_of_blocks);
		int get_free_index(int number_of_blocks);
		void allocate_blocks(int index, int num_of_blocks);

	public:
		heap() {
		}

		heap(void* start, dword block_size) {
			initialize(start, block_size);
		}

		void initialize(void* start, dword block_size);
		void* allocate(dword size);
		
		void read_entry_from_address(void* address, int* block_index, word* num_of_blocks);
		void* create_entry(int block_index, word num_of_blocks);

		void free(void* address);

		template <typename T>
		T* allocate() {
			return (T*)allocate(sizeof(T));
		}
	};
}
