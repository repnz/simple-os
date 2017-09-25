[bits 32]
section .data

temp_eip dd 0
temp_esp dd 0
temp_eax dd 0

section .text


%macro ISR_NOERRCODE 1
; This macro creates a stub for an ISR which does NOT pass it's own
; error code (adds a dummy errcode byte).
global isr%1
  isr%1:
    cli                         ; Disable interrupts firstly.
    push dword 0                 ; Push a dummy error code.
    push dword %1                ; Push the interrupt number.
    jmp isr_common_stub         ; Go to our common handler code.
%endmacro
%macro ISR_ERRCODE 1
; This macro creates a stub for an ISR which passes it's own
; error code.
  global isr%1
  isr%1:
    cli                         ; Disable interrupts.
    push dword %1                ; Push the interrupt number
    jmp isr_common_stub
%endmacro

extern isr_handler

global isr_common_stub
; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pushad                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
  
	call isr_handler
	
	popad
	add esp, 8

	iret

	; take esp to temp
	;mov eax, dword [esp+3*4] 
	;mov dword [temp_esp], eax 

	; restore all registers
	;popad

	; save eax in temp
	;mov dword [temp_eax], eax

	; clear the interrupt number and exception code
	;add esp, 8 

	; save eip in the side
	;pop dword [temp_eip]
	
	;pop eax
	
	; restore eflags, FROM HERE ON DONT CHANGE FLAGS
	;popfd

	;mov eax, dword [temp_eax]
	;mov esp, dword [temp_esp]

	; enable interrupts again
	;sti

	;jmp dword [temp_eip]


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 32
ISR_NOERRCODE 33
ISR_NOERRCODE 34
ISR_NOERRCODE 35
ISR_NOERRCODE 36
ISR_NOERRCODE 37
ISR_NOERRCODE 38
ISR_NOERRCODE 39
ISR_NOERRCODE 40
ISR_NOERRCODE 41
ISR_NOERRCODE 42
ISR_NOERRCODE 43
ISR_NOERRCODE 44
ISR_NOERRCODE 45
ISR_NOERRCODE 46
ISR_NOERRCODE 47
ISR_NOERRCODE 48