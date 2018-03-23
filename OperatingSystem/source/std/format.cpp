#include <std/format.h>

static const char* numbers = "0123456789abcdef";

namespace std 
{
	int format::num_to_string(char* buffer, const dword number, const byte base) 
	{
		char temp_buf[32];

		const int index = num_to_string_reverse(temp_buf, number, base);

		for (int i = 0, j = index - 1; i<index; ++i, j--) 
		{
			buffer[i] = temp_buf[j];
		}

		buffer[index] = 0;
		return index;
	}

	int format::num_to_string_reverse(char* buffer, dword number, const byte base) 
	{
		int index = 0;

		do 
		{
			buffer[index++] = numbers[number % base];
			number /= base;
		} 
		while (number != 0);

		return index;
	}
}
