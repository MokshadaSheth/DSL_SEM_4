%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro


section .data
	m1 db "The processor is in protected mode",10;
	m1Len equ $-m1
	m2 db "The processor is not in potected mode",10;
	m2Len equ $-m2
	
section .bss
	gdtrv resb 6
	v1 resb 4
	v2 resb 2
	ans resb 2
	base resb 4
	count resb 2
	
	section .text
	global _start
	
	
	
	_start:
			SMSW ax
			checkAX:
			BT ax,0
			
			JC inProtection
			rw 01,m2,m2Len
			jmp cont
			
			inProtection:
					rw 01,m1,m1Len
					
			cont:
					SGDT [gdtrv]
					mov eax, dword[gdtrv]
					checkEax:
					mov dword[v1],eax
					call htoa32
					
					rw 01,m1,m1Len
					mov dword[v1],12345678h
					call htoa32
					
					mov word[v2],1234h
					;call htoa16
					jmp exit

htoa32:
	mov eax,dword[v1]
	mov ebx,base		
	mov byte[count],8
	
	repeat:
			rol al,04h
			mov dl,al
			and dl,0Fh
			
			cmp dl,09h
			jle lessThanNine
			add dl,07h
			
			lessThanNine:
					add dl,30h
					mov [ebx],dl
					inc ebx
					dec byte[count]
					jnz repeat
					
			rw 01,base,8		
ret

htoa16:
	mov ax,word[v2]   ;Changing this
	mov ebx,ans
	mov byte[count],4
	
	again:
	rol al,04h
	mov dl,al
	and dl,0Fh
	
	cmp dl,09h
	jle x
	add dl,07h
	
	x:
	add dl,30h
	mov [ebx],dl
	inc ebx
	dec byte[count]
	jnz again
	

	rw 01,ans,4
ret	
				
exit:
mov rax,60
mov rdi,00
syscall	
