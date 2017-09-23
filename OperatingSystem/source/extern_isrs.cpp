#include <extern_isrs.h>

extern "C" {
	extern void isr0();
	extern void isr1();
	extern void isr2();
	extern void isr3();
	extern void isr4();
	extern void isr5();
	extern void isr6();
	extern void isr7();
	extern void isr8();
	extern void isr9();
	extern void isr10();
	extern void isr11();
	extern void isr12();
	extern void isr13();
	extern void isr14();
	extern void isr15();
	extern void isr16();
	extern void isr17();
	extern void isr18();
	extern void isr19();
	extern void isr20();
	extern void isr21();
	extern void isr22();
	extern void isr23();
	extern void isr24();
	extern void isr25();
	extern void isr26();
	extern void isr27();
	extern void isr28();
	extern void isr29();
	extern void isr30();
	extern void isr31();
	extern void isr32();
	extern void isr33();
	extern void isr34();
	extern void isr35();
	extern void isr36();
	extern void isr37();
	extern void isr38();
	extern void isr39();
	extern void isr40();
	extern void isr41();
	extern void isr42();
	extern void isr43();
	extern void isr44();
	extern void isr45();
	extern void isr46();
	extern void isr47();
	extern void isr48();
}

typedef void(*function)();

const function arr[] = 
{
	isr0,
	isr1,
	isr2,
	isr3,
	isr4,
	isr5,
	isr6,
	isr7,
	isr8,
	isr9,
	isr10,
	isr11,
	isr12,
	isr13,
	isr14,
	isr15,
	isr16,
	isr17,
	isr18,
	isr19,
	isr20,
	isr21,
	isr22,
	isr23,
	isr24,
	isr25,
	isr26,
	isr27,
	isr28,
	isr29,
	isr30,
	isr31,
	isr32,
	isr33,
	isr34,
	isr35,
	isr36,
	isr37,
	isr38,
	isr39,
	isr40,
	isr41,
	isr42,
	isr43,
	isr44,
	isr45,
	isr46,
	isr47,
	isr48
};

void* get_extern_address(word offset) {
	return (void*)arr[offset];
}