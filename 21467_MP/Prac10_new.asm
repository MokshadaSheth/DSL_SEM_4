%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

section .bss
			argIp resb 1
			result resb 4
			
section .data

section .text

global _start

_start:

pop rbx
pop rbx
pop rbx

mov [argIp],rbx;
rw 1,argIp,1

exit:
mov rax,60
mov rdi,00
syscall	
