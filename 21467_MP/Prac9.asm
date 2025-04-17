%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

section .data
fname db "data.txt",0

section .bss
buffer resb 100
fd resq 1
;global buffer
global _start

section .text
;extern

_start:

		mov rax,02
		mov rdi,fname
		mov rsi, 02h
		mov rdx, 0777h
		syscall
		
		temp:
		;read
		mov rax,00
		mov rdi,[fd]
		mov rsi,buffer
		mov rdx,100
		syscall
		check:
		rw 01,buffer,100
		
		;exit flie
		mov rax , 3
		mov rdi, [fd]
		syscall
		
		

exit:
mov rax,60
mov rdi,00
syscall	
