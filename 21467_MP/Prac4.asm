%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

;----------------------
;Aithmetic Operations
;----------------------


section .data
	snum1 dq 1234h
	snum2 dq 1232h
	unnum1 dq 12h
	unnum2 dq 12h
	m1 dw 18h
	m2 dw 02h
	divisor db 02h
	
	menu db 10,13,"Menu",10,13,"1.Add",10,13,"2.Sub",10,13,"3.Mul",10,13,"4.Div",10,13,"5.Signed Mul",10,13,"6.Signed Div",10,13,"7.Exit",13,10,"Enter Choice code: ";
	menuLen equ $-menu
	
	section .bss
	choice resb 2
	result resq 1
	ans resb 16
	count resb 16
	
	global _start
	section .text
	
	_start:
			loop: ;till choice code is 7
				rw 01,menu,menuLen
				rw 00,choice,2                 ;In choice we have ascii hex i.e 30,31,...
				
				;---------Switch Case----------
				cmp byte[choice],31h
				jne case2
				call addProc ;Calling if equal
				call htoa
				jmp ending
				
				case2:
				cmp byte[choice],32h
				jne case3
				call subProc
				call htoa
				jmp ending
				
				case3:
				cmp byte[choice],33h
				jne case4
				call mulProc
				call htoa
				jmp ending
				
				case4:
				cmp byte[choice],34h
				jne case5
				call divProc
				call htoa
				jmp ending
				
				case5:
				cmp byte[choice],35h
				jne case7
				call signMul
				call htoa
				jmp ending
				
				case7:
				
				
				ending:
				cmp byte[choice],37h
				mov byte[choice],00h
				jne loop
				jmp exit
	
;----Add Proc
addProc:
	mov rax,qword[snum1]
	add rax,qword[snum2]
	mov qword[result],rax
ret		

;----Sub Proc
subProc:
		mov rax,qword[snum1]
		sub rax,qword[snum2]
		mov qword[result],rax
ret

;----Mul Proc
mulProc:
		mov ax,[m1]
		mov dx,[m2]
		mul dx
		checkMul:
		mov qword[result],rax
ret

;----Signed Mul
signMul:
		mov ax,[m1]
		mov dx,[m2]
		imul dx
		mov qword[result],rax
ret

;----Div            Note: Dividend should be of double size that of divisor
divProc:
		mov rax,0
		mov ax,word[m1]
		mov dl,byte[divisor]
		div dl
		checkDiv:
		mov qword[result],rax
ret

;---ASCII to HEX			
htoa:
	mov rax,qword[result]   ;Changing this
	mov rbx,ans
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
	

	rw 01,ans,16
	c:
ret	
				
exit:
mov rax,60
mov rdi,00
syscall	

