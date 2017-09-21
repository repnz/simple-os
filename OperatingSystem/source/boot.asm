[bits 16]
global start

; linker variables
extern __stack_start__
extern __kernel_start_sector__
extern __kernel_sectors_length__
extern __kernel_memory_start__

; kernel variables
extern kernel_entry

; gdt.asm variables
extern gdt_descriptor

drive equ 0x80

start:
	jmp 0000:fix_cs_register

fix_cs_register:
	cli
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax
	mov gs, ax

	mov sp, __stack_start__
	mov bp, __stack_start__
	
	mov si, load_msg
	call print_string
	
	call reset_disk_drive

	mov cl, __kernel_start_sector__
	mov al, __kernel_sectors_length__
	mov bx, __kernel_memory_start__

	call load_sectors

	jmp move_to_protected_jump

reset_disk_drive:
	mov ah, 0
	mov dl, drive
	int 0x13
	jnc .done
	mov si, error_reset_disk
	call print_string
.done:
	ret

load_sectors: ; cl = sector number, al = number of sectors to load, es:bx address to load
	mov dl, drive
	mov dh, 0     ; head
	mov ch, 0     ; cylinder
	mov ah, 2
	int 0x13
	jnc .done
	
	; print error
	mov si, error_loading
	call print_string

	mov si, error_loading
	call print_string
	jmp wait_forever
.done:
	ret

print_string: ; si = c string pointer
	.print_loop:
		lodsb ; load char from si into al

		; if char is zero end done
		test al, al
		jz .done
	
		mov ah, 0x0e ; 0x0e function for teletype printing character
		mov bx,0 ; set pageNumber and color to 0
		int 0x10
		jmp .print_loop
	.done:
		ret

wait_forever:
	mov si, sleep
	call print_string
	jmp $                        ; endless loop

move_to_protected_jump:
	xor ax, ax
	mov ds, ax

	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp 08:protected_mode_initialize

[bits 32]
protected_mode_initialize: ; cs=0x08 to index GDT_CODE
	cli
	mov ax, 0x10 
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov gs, ax
	mov fs, ax
	
	mov esp, __stack_start__
	mov ebp, __stack_start__

	call kernel_entry
	jmp $

load_msg db "Loading Kernel..", 10, 13, 0
error_loading db "Error Reading Sectors!", 10, 13, 0
error_reset_disk db "Error Reseting disk drive!", 10, 13, 0
sleep db "Sleep Forever", 10, 13, 0