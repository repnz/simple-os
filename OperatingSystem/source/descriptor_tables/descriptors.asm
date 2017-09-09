[bits 32]
global gdt_entries
global gdt_descriptor
global idt_flush
global gdt_flush

GDT_FLAGS_32_BIT_SIZE      equ 01b
GDT_FLAGS_16_BIT_SIZE      equ 00b
GDT_FLAGS_BYTE_GRANULARITY equ 00b
GDT_FLAGS_PAGE_GRANULARITY equ 10b



GDT_ACCESS_ACCESSED         equ 00000001b
GDT_ACCESS_NOT_ACCESSED     equ 00000000b
GDT_ACCESS_RW               equ 00000010b
GDT_ACCESS_GROW_DOWN        equ 00000100b
GDT_ACCESS_EXECUTABLE       equ 00001000b
GDT_ACCESS_DEFAULT_BIT      equ 00010000b
GDT_ACCESS_RING_LEVEL_0     equ 00000000b
GDT_ACCESS_RING_LEVEL_1     equ 00100000b
GDT_ACCESS_RING_LEVEL_2     equ 01000000b
GDT_ACCESS_RING_LEVEL_3		equ 01100000b
GDT_ACCESS_PRESENT			equ 10000000b

GDT_CODE_ACCESS_BYTE       equ GDT_ACCESS_DEFAULT_BIT | GDT_ACCESS_PRESENT | GDT_ACCESS_RING_LEVEL_0 | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_RW 
GDT_DATA_ACCESS_BYTE       equ GDT_ACCESS_DEFAULT_BIT | GDT_ACCESS_PRESENT | GDT_ACCESS_RING_LEVEL_0 | GDT_ACCESS_RW

GDT_CODE_FLAGS                  equ GDT_FLAGS_32_BIT_SIZE  | GDT_FLAGS_PAGE_GRANULARITY
GDT_DATA_FLAGS                  equ GDT_FLAGS_32_BIT_SIZE  | GDT_FLAGS_PAGE_GRANULARITY




gdt_entries:
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff    ; limit low
    dw 0x0       ; base low
    db 0x0       ; base_middle 
    db GDT_CODE_ACCESS_BYTE
    db (GDT_CODE_FLAGS << 6) | 0xF ; flags, limit high bits
    db 0x0       ; base high bits

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db GDT_DATA_ACCESS_BYTE 
    db (GDT_DATA_FLAGS << 6) | 0xF
    db 0x0

times 253*8 db 0

gdt_end:
gdt_descriptor:
	dw gdt_end - gdt_start
	dd gdt_start	


gdt_flush: ; gdt_flush(descriptor* d)
	mov eax, dword [esp+4]
	lgdt [eax]
	ret

idt_flush: ; idt_flush(descriptor* d)
	mov eax, dword [esp+4]
	lidt [eax]
	ret