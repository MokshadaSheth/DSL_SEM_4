%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

section .data
arr dq 30h,40h,50h,10h,70h
dst dq 0,0,0,0,0

m1 db 10,13,"Source:",10,13;
l1 equ $-m1
m2 db 10,13," Value:",10,13;
l2 equ $-m2
m3 db 10,13,"Destination:",10,13;
l3 equ $-m3

section .bss
cnt resb 1
count resq 1
var resq 1
ans resb 16


global _start
	section .text
	
	_start:
	rw 01,m1,l1
    
	mov rsi,arr
	call print_arr
	
 
 ;---Main logic
 mov rsi,arr+32
 mov rdi, arr+56
 
 mov rcx, 05h
 std    ;Direction flag 
 rep movsq
  
 ;--------Destination
     rw 01,m3,l3
 
	mov rsi,dst-16 ;;IMP
	
	call print_arr
 
jmp exit


;Source and destination address and content
print_arr:
    mov byte[cnt],05h
    loop:
	mov qword[var],rsi
	
	push rsi
	call htoa
	pop rsi
	
	mov rax,[rsi]   ;Content in RSI
	mov qword[var],rax
	
	push rsi
	call htoa

	pop rsi
	
	add rsi,08
	dec byte[cnt]
	jnz loop
ret



;---ASCII to HEX			
htoa:
	mov rax,qword[var]   ;Changing this
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
	rw 01,m2,l2
	
ret	
				
exit:
mov rax,60
mov rdi,00
syscall	
