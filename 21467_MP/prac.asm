%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro


section .data

m1 db "Enter 5 numbers: ", 10
l1 equ $-m1
m2 db "Display: ",10
l2 equ $-m2


section .bss
numarr resb 85


global _start
section .text

_start:


mov rbx,numarr

rw 01,m1,l1
count db 05h
x:
rw 00,rbx,17
add rbx,17
dec byte[count]
jnz x

rw 01,m2,l2
mov count,[05]
y:
rw 01,rbx,17
add rbx,17
dec byte[count]
jnz y
	
mov rax,60
mov rdi,00
syscall
