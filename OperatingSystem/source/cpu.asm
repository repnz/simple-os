[bits 32]

global get_flags

get_flags:
	pushf
	pop eax
	ret