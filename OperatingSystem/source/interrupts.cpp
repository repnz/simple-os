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

interrupts::interrupt_handler interrupt_handlers[255];

void interrupts::initialize() {
	memset(interrupt_handlers, 0, 255*sizeof(interrupts::interrupt_handler));

	descriptor_tables::idt::clear();

	for (word i = 0; i < 255; ++i) {
		void* addr = get_extern_address(i);
		descriptor_tables::idt::set_entry(i, addr, 0x8);
	}

	descriptor_tables::idt::flush();
}

void interrupts::enable() {
	ASM_VOLATILE("sti");
}

void interrupts::add_handler(dword interrupt_code, interrupt_handler handler) {
	interrupt_handlers[interrupt_code] = handler;
}

GLOBAL void isr_handler(interrupts::interrupt_frame frame) {
	
	if (interrupt_handlers[frame.int_no] != 0 && frame.int_no < 255) {
		interrupt_handlers[frame.int_no](frame);		
	}
	else if (frame.int_no <= 18) {
		devices::vga::write_text(exception_messages[frame.int_no]);
		devices::vga::write_char(' ');
		while (true);
	}
	else {
		devices::vga::write_text("cannot handle interrupt ");
		devices::vga::write_number(frame.int_no);
		devices::vga::write_char(' ');
		while (true);
	}
}