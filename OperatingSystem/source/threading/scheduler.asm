[bits 32]

section .data

tmp_new_esp dd 0
tmp_new_eip dd 0

section .text
extern current_thread_state

global restore_thread_state

restore_thread_state:
	cli
	; index the regs member
	mov esp, dword [current_thread_state]
	add esp, 4
	pop edi
	pop esi
	pop ebp
	pop dword [tmp_new_esp]
	pop ebx
	pop edx
	pop ecx
	pop eax
	popf 
	pop dword [tmp_new_eip]
	mov esp, [tmp_new_esp]
	sti
	jmp dword [tmp_new_eip]
