
%macro rw 3
	mov rax,%1
	mov rdi,%1
	mov rsi,%2
	mov rdx,%3
	syscall
%endmacro

section .data
	menu db 0xa, "----------Menu----------", 10, "1. HEX TO BCD", 10, "2. BCD TO HEX", 10, "3. Exit", 10, 10, "Enter choice : "
	menulen equ $-menu
	
	s1 db "Enter 4 digit HEX number : ",10,10," HEX : "  
	op1len equ $-s1
	
	s2 db "Enter 5 digit BCD number : ",10,10," BCD : "
	op2len equ $-s2
	
	s3 db " BCD : "
	op3len equ $-s3
	
	s4 db " HEX : "
	op4len equ $-s4
	
	umsg db "h", 0xa, 10
	umsglen equ $-umsg
	
	nm db 10
	nml equ $-nm
	
	invalid db "Invalid Choice !",10
	invml equ $-invalid
	
	
section .bss
	num resb 5
	bcd resb 6
	choice resb 2
	count resb 1
	res resb 1
	ans resb 16
global _start
section .text
_start:
	loop_back:
	rw 1, menu, menulen
	rw 0, choice, 2
	
	rw 1,nm,nml
	
	cmp byte[choice], 31h
	je h2b_case
	
	cmp byte[choice], 32h
	je b2h_case
	
	cmp byte[choice], 33h
	je exit
	
	jmp invalid_choice
	
	h2b_case:
		rw 1,s1,op1len		
		rw 0,num,5
		call a2h
		call hextobcd
		rw 1,nm,nml
		jmp loop_back
		
	b2h_case:
		rw 1,s2,op2len		
		rw 0,bcd,6
		call BcdtoHex
		call h2a16
		rw 1,s4,op4len
		rw 1,ans,4
		rw 1,nm,nml
		jmp loop_back
		
	
	invalid_choice:
		rw 1,invalid,invml
		jmp exit
		
	
	hextobcd:
		mov bx,10
		mov byte[count],0
		back:
			xor dx,dx
			div bx
			push dx
			inc byte[count]
			cmp ax,0
			jnz back
		rw 1,s3,op3len
		back1:
			pop dx
			add dl,30h
			mov [res],dl
			rw 1,res,1
			dec byte[count]
			jnz back1
		ret
		
	BcdtoHex:
		mov rsi, bcd
		xor rax,rax
		mov byte[count],5
		mov rbx, 10
		next:
			xor cx,cx
			mul rbx
			mov cl, [rsi]
			sub cl, 30h
			add ax,cx
			inc rsi
			dec byte[count]
			jnz next
		ret
	
	a2h:
		mov byte[count],4
		mov rbx, num
		again:
			mov dl,[rbx]
			cmp dl,39h
			jbe y
			sub dl,07h
			y:
				sub dl,30h
			shl ax,4
			or al,dl
			inc rbx
			dec byte[count]
			jnz again
			ret
	
		h2a16:	
			mov rbx, ans
			mov byte[count], 4
			again2:
				rol ax,04h
				mov dx,ax
				and dx, 0Fh
				cmp dl, 09h
				jle x
				add  dl, 07h
				x:
					add dl, 30h
				mov [rbx], dl
				inc rbx
				dec byte[count]
				jnz again2
			ret
	
	exit:
		mov rax,60
		mov rdi,0
		syscall
