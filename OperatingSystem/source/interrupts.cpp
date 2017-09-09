#include <interrupts.h>
#include <descriptor_tables/idt.h>
#include <devices/vga.h>
#include <extern_isrs.h>

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
const char *exception_messages[] =
{
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check"
};


void interrupts::initialize() {
	
	descriptor_tables::idt::clear();

	for (word i = 0; i < 255; ++i) {
		void* addr = get_extern_address(i);
		descriptor_tables::idt::set_entry(i, addr, 0x8);
	}

	descriptor_tables::idt::flush();

	ASM_VOLATILE("sti");	
}

void interrupts::add_handler(dword interrupt_code, interrupt_handler handler) {
}



GLOBAL void isr_handler(const interrupts::interrupt_frame r) {
	devices::vga::write_number(r.int_no);
	devices::vga::write_text(" ");
	devices::vga::write_number(r.err_code);
}