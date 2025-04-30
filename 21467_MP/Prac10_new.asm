%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

section .data
    msg db "Enter number: ",10
    msgLen equ $-msg
    msg2 db "Factorial is: ",10
    msg2Len equ $-msg2
    fact1 db "1",10
    fact1Len equ $-fact1
    num db 05h
    
section .bss
	ans resb 1
    ;num resb 2
    
global _start
section .text
    
_start:
    ; rw 00,num,2
    ; mov al, [num]
    ; sub al, '0'
    ; mov [num],bl
    ; rw 01,num,2

    rw 01,msg,msgLen
    mov bl, [num]
    cmp bl,01h
    jle fact_1

    call fact
    mov byte[ans],al
    call htoa
    jmp exit

fact_1:
    rw 01,msg2,msg2Len
    rw 01,fact1,fact1Len
    jmp exit

;-------Recursive Procedure (FIXED)
fact:
    cmp bl,1
    jne cal_fact
    mov ax,1
    ret

cal_fact:
   push rbx
   dec bl
   call fact

   pop rbx
   mul bl
   ret

;----Hex to ASCII
htoa:
    mov al,byte[ans]
    mov cl,2
    mov rsi,ans
again:
    rol al,4
    mov bl,al
    and bl,0Fh

    cmp bl,09h
    jle add30
    add bl,07h

add30:
    add bl,30h

    mov [rsi], bl
    inc rsi
    dec cl
    jnz again

    rw 01,msg2,msg2Len
    rw 01,ans,4

    ret

exit:
	mov rax,60
	mov rdi,0
	syscall
