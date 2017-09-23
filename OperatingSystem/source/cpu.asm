[bits 32]

global get_flags

get_flags:
	pushf
	pop eax
	ret

set_regs:
	add esp, 4  ; skip function return address
	popa
	sub esp, 36 ; return back to return address
	ret