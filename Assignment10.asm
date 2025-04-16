%macro rw 3
mov rax,%1
mov rdi,01
mov rsi,%2
mov rdx,%3 
syscall
%endmacro

section .bss
num resb 2          ;single digit number
factres resb 4      ;2 digit number
count resb 4
res_ascii resb 4    ;

section .data
count1 db 04

section .text
global _start:
_start:

pop rbx             ;pop arguement list
pop rbx             ;pop program number
pop rbx             ;pop input value

mov [num], rbx      ; mov rbx value in num
call ascii_hex      ;just user input therefore ascii to hex

mov rax,rbx         ;for use of mul destination rax default

fact:
	dec rbx     ;reduce value ex:4 after dec 3
	cmp rbx,01  ;return done calculation
	je l1
	cmp rbx,00  ; return 1
	je l2
	mul rbx     ; souce rax*rbx
	call fact
	
l1:
	mov [factres],rax  ;result stored in rax moved to variable
	call hex_to_ascii
	jmp exit
l2: 
	mov byte[factres],00h
	call hex_to_ascii
	jmp exit
	
ascii_hex:
	mov al,byte[num]
	rol al, 04h
	mov dl, al
	sub dl, 0fh

	cmp dl, 09h
	jle x
	sub dl, 07h
	
	x: 
	sub dl,30h
	mov [rbx], dl
	inc rbx
	dec byte[count1]
	jnz ascii_hex
	
	mov byte[count1],4
	rw 01,res_ascii,4                ; print result
	ret
	
hex_to_ascii:
	mov al,byte[num]
	rol al, 04h
	mov dl, al
	and dl, 0fh

	cmp dl, 09h
	jle x
	add dl, 07h
	
	x1: 
	add dl,30h
	mov [rbx], dl
	inc rbx
	dec byte[count1]
	jnz hex_to_ascii

	rw 01,factres,4                ; print result
	ret
	
exit:
	mov rax,60
	mov rdi,00
	syscall
	
	

