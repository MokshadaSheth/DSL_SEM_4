%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

section .bss
count resb 16
arr resb 16

global _start

section .text

_start:

mov rax, 43891FCD1128CDFFh
mov rbx,arr ;Pointer
mov byte[count],16

again:
	rol rax,04h
	mov dl,al
	and dl,0Fh
	
	cmp dl,09h
	jle x
	add dl,07h
	
x:
	add dl,30h
	mov [rbx],dl
	inc rbx
	dec byte[count]
	jnz again
	
rw 01,arr,16

mov rax,60
mov rdi,00
syscall	
