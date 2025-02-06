%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

;-------------------------------------
;Count Negative and Positive numbers
;-------------------------------------

section .data
m1 db "Total Positive Numbers: "
l1 equ $-m1
m2 db "Total Negative Numbers: "
l2 equ $-m2
arr dq 3h,03h,8000000000000000h,0C2h
count db 04h
pcount db 00h
ncount db 00h
cnt db 02h


section .bss
value resb 02
ans resb 02

global _start

section .text

_start:

mov rdi,arr

loop:
mov rax,[rdi]
BT rax,63
JC negative
	
	inc byte[pcount]
	jmp next

negative:
				
				inc byte[ncount]
next:
			add rdi,08
			dec byte[count]
			jnz loop
		

mov cl,byte[pcount]
mov byte[value],cl

rw 01,m1,l1
call htoa   ;Calling Procedure

mov bl,byte[ncount]
mov byte[value],bl

rw 01,m2,l2
call htoa
check:			

htoa:
	mov al,byte[value]
	mov rbx,ans
	l:
		rol al,04h
		mov dl,al
		and dl,0Fh
		
		cmp dl,09h 
		jle lessThanNine
		add dl,07h
	
	lessThanNine:
		add dl,30h        ;Always executes
		mov [rbx],dl   ; mov answer
		inc rbx
		dec byte[cnt]
		jnz l
		ansCheck:
		mov byte[ans],dl  ; get ascii result back in ans
		rw 01,ans,02
ret 


exit:
mov rax,60
mov rdi,00
syscall			

				
				

