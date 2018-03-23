#include <memory/heap.h>
#include <std/mem.h>

#include <text_mode/console.h>
using text_mode::console;


//#define DEBUG_MEMORY_ALLOCATION


namespace memory 
{

	int heap::search_free_index(int start_search, int end_search, int num_of_blocks)
	{
		for (int i = start_search; i < end_search; i += num_of_blocks) 
		{
			if (!std::mem::has_value(_entries + i, true, num_of_blocks)) 
			{
				return i;
			}
		}

		return -1;
	}

	int heap::get_free_index(int number_of_blocks) 
	{

		int end_search = entries_size - number_of_blocks;

#ifdef DEBUG_MEMORY_ALLOCATION
		console::write_text("start search in [");
		console::write_number(_current_index);
		console::write_text(", ");
		console::write_number(end_search);
		console::write_text("] ");
#endif
		// search from current index to end
		int free_index = search_free_index(_current_index, end_search, number_of_blocks);

		if (free_index != -1) { return free_index; }

#ifdef DEBUG_MEMORY_ALLOCATION
		console::write_text(" second scan ");
#endif
		// search from 0 to current index
		return search_free_index(0, _current_index, number_of_blocks);
	}

	void heap::allocate_blocks(int index, int num_of_blocks) 
	{
		_current_index = index + num_of_blocks;

		// set to used
		std::mem::set<bool>(_entries + index, true, num_of_blocks);
	}

	void heap::initialize(void* start, dword block_size)
	{
		_start = start;
		_block_size = block_size;
		_current_index = 0;
		std::mem::set<bool>(_entries, false, entries_size);
	}

	void* heap::allocate(dword size) {
		size += sizeof(word);

#ifdef DEBUG_MEMORY_ALLOCATION
		console::write_text("allocate size=");
		console::write_number(size);
		console::write_text(" , ");
#endif

		word num_of_blocks = 1;

		if (size > _block_size) 
		{
			num_of_blocks = size / _block_size;

			if ((size % _block_size) != 0) 
			{
				num_of_blocks += 1;
			}
		}

#ifdef DEBUG_MEMORY_ALLOCATION
		console::write_text("num_of_blocks=");
		console::write_number(num_of_blocks);
#endif

		int free_index = get_free_index(num_of_blocks);

#ifdef DEBUG_MEMORY_ALLOCATION	
		console::write_text(" , free_index=");
		console::write_number(free_index);
#endif

		if (free_index == -1) 
		{
			return 0; 
		}

		allocate_blocks(free_index, num_of_blocks);

#ifdef DEBUG_MEMORY_ALLOCATION
		console::write_text(", new_current_index=");
		console::write_number(_current_index);
		console::write_text("\r\n");
#endif

		return create_entry(free_index, num_of_blocks);
	}

	void heap::read_entry_from_address(void* address, int* block_index, word* num_of_blocks) 
	{
		byte* origin = ((byte*)address - sizeof(word));
		word* num_of_blocks_address = (word*)origin;
		*num_of_blocks = *num_of_blocks_address;
		*block_index = ((dword)origin - (dword)_start) / _block_size;
	}	

	void* heap::create_entry(int block_index, word num_of_blocks) 
	{
		byte* origin = ((byte*)_start + (block_index * _block_size));
		word* num_of_block_address = (word*)origin;
		*num_of_block_address = num_of_blocks;
		return (origin + sizeof(word));
	}

	void heap::free(void* address) 
	{
		int block_index;
		word num_of_blocks;

		read_entry_from_address(address, &block_index, &num_of_blocks);

#ifdef DEBUG_MEMORY_ALLOCATION
		console::write_text("free block_index=");
		console::write_number(block_index);
		console::write_text(" num_of_blocks=");
		console::write_number(num_of_blocks);
#endif

		if (std::mem::has_value(_entries + block_index, false, num_of_blocks)) 
		{
			console::write_text("FREE ERROR\r\n");
			while (true);
		}

		std::mem::set<bool>(_entries + block_index, false, num_of_blocks);
	}
}
