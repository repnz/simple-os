#pragma once

template <dword entries_size>
class entries_heap {
private:
	void* _start;
	int _block_size;
	int _current_index;
	bool _entries[entries_size];

	int get_free_index(int number_of_blocks) {

		if (_current_index + number_of_blocks > entries_size) {
			_current_index = 0;
		}
		
		int end_search = entries_size - number_of_blocks;
		
		while (_current_index < end_search) {
			bool found = mem::has_value(_entries+_current_index, true, number_of_blocks);

			if (found) {
				_current_index += number_of_blocks;
			}
			else {
				return _current_index;
			}
		}

		return -1;
	}

	void allocate_blocks(int index, int num_of_blocks) {
		devices::vga::write_number(num_of_blocks);
		devices::vga::write_char(' ');
		_current_index = index + num_of_blocks;

		// set to used
		mem::set<bool>(_entries, true, num_of_blocks);
	}

public:
	entries_heap(void* start, dword block_size) :
	_start(start), _block_size(block_size), _current_index(0){
		mem::set<bool>(_entries, false, entries_size);
	}

	void* allocate(dword size) {
		
		size += 2;

		word num_of_blocks;

		if (size < _block_size) {
			num_of_blocks = 1;
		}
		else {
			word num_of_blocks = size / _block_size;

			if (size % _block_size != 0) {
				num_of_blocks += 1;
			}
		}
		
		int free_index = get_free_index(num_of_blocks);

		if (free_index == -1) { return 0; }
		
		allocate_blocks(free_index, num_of_blocks);

		word* address = (word*)(((byte*)_start) + (free_index * _block_size));
		*address = num_of_blocks;
		return (byte*)address + 2;
	}

	void free(void* address) {
		byte* original_address = (byte*)address - 2;
		word num_of_blocks = *(word*)(original_address);
			
	}

	template <typename T>
	T* allocate() {
		return (T*)allocate(sizeof(T));
	}
};