%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

section .data
m1 db "Enter String:" ,10
l1 equ $-m1
m2 db "Length:",10
l2 equ $-m2

section .bss
mystr resb 20
lenvar resb 01

global _start
section .text


_start:

rw 01,m1,l1
rw 00,mystr,20

x:
cmp al,09h
jle y
add al,07h

y:
add al, 30h
mov byte[lenvar],al
 

rw 01,m2,l2  ; To display Length:
rw 01,lenvar,01

mov rax,60
mov rdi,00
syscall
