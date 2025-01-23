section .bss
num resb 2

global _start
section .text

_start:
mov rax,0
mov rdi,0
mov rsi,num
mov rdx,02
syscall

mov rax,1
mov rdi,1
mov rsi,num
mov rdx,02

syscall

mov rax, 60
mov rdi, 60
syscall
