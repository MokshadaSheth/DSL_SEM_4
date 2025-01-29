%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

;--------------------------------------
;  TO FIND LARGEST DIGIT IN ARRAY
;--------------------------------------

section .data
m1 db "Largest Digit is: ",10
l1 equ $-m1
numarr db 10h,05h,01h
count db 03h

section .bss
	
	
global _start
section .text

_start:


rw 01,m1,l1

mov rax, 10h
mov rbx,numarr ;Pointer
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
	
rw 01,numarr,16

mov rax,60
mov rdi,00
syscall
