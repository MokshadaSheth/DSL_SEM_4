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
numarr db 2h,3h,0cfh
count db 03h
cnt db 02h

section .bss
largest resb 01	
ans resb 02
	
global _start
section .text

_start:

mov rdi,numarr
mov al,00h ; Initially it is 0

loop:
	cmp al,[rdi]
	ja incPointer         ;------Note:If jg 03 is largest as it considers CF as negative thus use ja
	mov al,[rdi]  ;if al is not large then only
	
	incPointer:
	inc rdi ;always executes
	
	dec byte[count]
	jnz loop  ;jump again to loop

check:	
mov byte[largest],al
	
call htoa

cont:
rw 01,m1,l1 ; At end string 
rw 01,ans,02

jmp exit


;Procedure to convert hex to ascii
htoa:
	mov al,byte[largest]
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
		;mov byte[ans],dl  ; get ascii result back in ans
		;rw 01,ans,02
ret 

exit:
mov rax,60
mov rdi,00
syscall
