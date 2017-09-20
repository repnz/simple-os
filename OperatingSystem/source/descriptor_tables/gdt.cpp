#include <descriptor_tables/gdt.h>
#include <descriptor_tables/descriptor.h>
#include <std/mem.h>
#include <std/compiler.h>

using namespace descriptor_tables;

#define GDT_SIZE 255

struct internal_gdt_entry {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;

	internal_gdt_entry(){
		dword* d = (dword*)this;
		d[0] = 0;
		d[1] = 0;
	}
} PACKED;


extern "C" {
	extern void gdt_flush(const descriptor& d);
	extern internal_gdt_entry gdt_entries[255];
}

void gdt::set_entry(word offset, dword base, dword limit, byte access, byte flags) {
	flags |= access::default_bit | access::present;

	/* Setup the descriptor base address */
	gdt_entries[offset].base_low = (base & 0xFFFF);
	gdt_entries[offset].base_middle = (base >> 16) & 0xFF;
	gdt_entries[offset].base_high = (base >> 24) & 0xFF;

	/* Setup the descriptor limits */
	gdt_entries[offset].limit_low = (limit & 0xFFFF);
	gdt_entries[offset].granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	gdt_entries[offset].granularity |= flags << 6;
	gdt_entries[offset].access = access;
}


void gdt::flush() {
	descriptor d(&gdt_entries, GDT_SIZE);
	gdt_flush(d);
}

static void initialize() {

	gdt_entries[0] = internal_gdt_entry();

	// code segment
	gdt::set_entry(
		0x8,
		0,
		0xFFFFFFFF,
		gdt::access::executable | gdt::access::ring_level_0
	);

	// data segment
	gdt::set_entry(
		0x10,
		0,
		0xFFFFFFFF,
		gdt::access::rw | gdt::access::ring_level_0
	);
	
	// stack segment
	gdt::set_entry(
		0x18, 
		0,
		0xFFFFFFFF,
		gdt::access::grow_down | gdt::access::ring_level_0 | gdt::access::rw
	);
}