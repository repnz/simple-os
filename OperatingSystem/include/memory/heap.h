#pragma once
#include <screen.h>

namespace memory {

	template <dword entries_size>
	class heap {
	private:
		void* _start;
		int _block_size;
		int _current_index;
		bool _entries[entries_size];

		int search_free_index(int start_search, int end_search, int num_of_blocks) {
			for (int i = start_search; i < end_search; i += num_of_blocks) {
				if (!mem::has_value(_entries + i, true, num_of_blocks)) {
					return i;
				}
			}

			return -1;
		}

		int get_free_index(int number_of_blocks) {
				
			int end_search = entries_size - number_of_blocks;
			screen::write_text("start search in [");
			screen::write_number(_current_index);
			screen::write_text(", ");
			screen::write_number(end_search);
			screen::write_text("] ");

			// search from current index to end
			int free_index = search_free_index(_current_index, end_search, number_of_blocks);

			if (free_index != -1) { return free_index; }

			screen::write_text(" second scan ");
			
			if (!_entries[0]) {
				screen::write_text("FIRST IS EMPTY???");
			}

			// search from 0 to current index
			return search_free_index(0, _current_index, number_of_blocks);
		}

		void allocate_blocks(int index, int num_of_blocks) {
			_current_index = index + num_of_blocks;

			// set to used
			mem::set<bool>(_entries, true, num_of_blocks);
		}

	public:
		heap() {
		}

		heap(void* start, dword block_size) {
			initialize(start, block_size);
		}

		void initialize(void* start, dword block_size) {
			/*
			screen::write_text("initializing heap with start=0x");
			screen::write_number((dword)start, 16);
			screen::write_text(";block_size=0x");
			screen::write_number(block_size, 16);
			screen::write_text(";length=");
			screen::write_number(entries_size);
			screen::write_text("\r\n");
			*/
			_start = start;
			_block_size = block_size;
			_current_index = 0;

			mem::set<bool>(_entries, false, entries_size);
		}

		void* allocate(dword size) {
			size += 2;

			screen::write_text("allocate size=");
			screen::write_number(size);
			screen::write_text(" , ");

			word num_of_blocks = 1;

			if (size > _block_size) {
				num_of_blocks = size / _block_size;

				if ((size % _block_size) != 0) {
					num_of_blocks += 1;
				}
			}

			screen::write_text("num_of_blocks=");
			screen::write_number(num_of_blocks);
			
			int free_index = get_free_index(num_of_blocks);
			screen::write_text(" , free_index=");
			screen::write_number(free_index);

			if (free_index == -1) { return 0; }

			allocate_blocks(free_index, num_of_blocks);
			
			screen::write_text(", new_current_index=");
			screen::write_number(_current_index);
			screen::write_text("\r\n");

			word* address = (word*)(((byte*)_start) + (free_index * _block_size));
			*address = num_of_blocks;
			return (byte*)address + 2;
		}

		void get_entry_from_address(void* address, int* block_index, word* num_of_blocks) {
			byte* original_address = (byte*)address - 2;
			*num_of_blocks = *((word*)(original_address));
			*block_index = (dword)(original_address - (dword)_start) / _block_size;
		}

		void free(void* address) {
			int block_index;
			word num_of_blocks;
			get_entry_from_address(address, &block_index, &num_of_blocks);
			
			screen::write_text("free block_index=");
			screen::write_number(block_index);
			screen::write_text(" num_of_blocks=");
			screen::write_number(num_of_blocks);
			

			mem::set<bool>(_entries + block_index, false, num_of_blocks);
		}

		template <typename T>
		T* allocate() {
			return (T*)allocate(sizeof(T));
		}
	};
}
