#include <descriptor_tables/gdt.h>
#include <descriptor_tables/descriptor.h>
#include <std/compiler.h>

using namespace descriptor_tables;

#define GDT_SIZE 255

struct internal_gdt_entry 
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;

	internal_gdt_entry()
	{
		dword* d = (dword*)this;
		d[0] = 0;
		d[1] = 0;
	}
} PACKED;


extern "C" 
{
	extern void gdt_flush(const descriptor& d);
	extern internal_gdt_entry gdt_entries[255];
}

void gdt::flush() 
{
	descriptor d(&gdt_entries, GDT_SIZE);
	gdt_flush(d);
}