#include <descriptor_tables/idt.h>
#include <descriptor_tables/descriptor.h>
#include <std/mem.h>
#include <std/compiler.h>

using namespace descriptor_tables;

struct internal_idt_entry 
{
	word func_low; // offset bits 0..15
	word selector; // a code segment selector in GDT or LDT
	byte zero;      // unused, set to 0
	byte type_attr; // type and attributes, see below
	word func_high; // offset bits 16..31
} PACKED;


extern "C" 
{
	extern void idt_flush(descriptor* d);
}

internal_idt_entry idt_entries[idt::size];

void idt::set_entry(word code, void* handler, word segment_selector, byte attributes) {
	attributes |= idt::attributes::present;

	idt_entries[code].func_low = (dword)handler & 0xFFFF;
	idt_entries[code].func_high = ((dword)handler >> 16) & 0xFFFF;
	idt_entries[code].selector = segment_selector;
	idt_entries[code].zero = 0;
	idt_entries[code].type_attr = attributes;
}

void idt::flush() {
	descriptor d(&idt_entries, idt::size*sizeof(internal_idt_entry));
	idt_flush(&d);
}

void idt::clear() {
	std::mem::zero<internal_idt_entry>(idt_entries, idt::size);
}