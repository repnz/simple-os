#include <mem.h>

void* memcpy(void* dest, const void* src, int count)
{
	unsigned char* destC = (unsigned char*)dest;
	unsigned char* srcC = (unsigned char*)src;
	
	for (int i = 0; i < count; i++)
		destC[i] = srcC[i];

	return dest;
}

void* memset(void* dest, byte val, int count)
{
	unsigned char* destC = (unsigned char*)dest;

	for (int i = 0; i < count; i++)
		destC[i] = val;
	return dest;
}

/* Same as above, but this time, we're working with a 16-bit
* 'val' and dest pointer.  Your code can be an exact copy of
* the above, provided that your local variables if any, are
* unsigned short */
void* memsetw(word* dest, word val, int count)
{
	
	int i;
	for (i = 0; i < count; i++)
		dest[i] = val;
	return dest;
}
