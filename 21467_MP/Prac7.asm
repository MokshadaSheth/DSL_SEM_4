%macro rw 3
mov rax, %1
mov rdi,01
mov rsi,%2
mov rdx, %3
syscall
%endmacro

section .data
    m1 db "The processor is in protected mode", 10
    m1Len equ $-m1

    m2 db "The processor is not in protected mode", 10
    m2Len equ $-m2

    m3 db "GDTR:", 10
    m3Len equ $-m3

    m4 db "IDTR:", 10
    m4Len equ $-m4

    m5 db "LDTR:", 10
    m5Len equ $-m5

    m6 db "TR:", 10
    m6Len equ $-m6

    labelBase db "Base: "
    labelBaseLen equ $-labelBase

    labelLimit db "Limit: "
    labelLimitLen equ $-labelLimit

    labelValue db "Value: "
    labelValueLen equ $-labelValue

    newLine db 10
    nL equ $-newLine

section .bss
    gdtrv resb 6
    idtrv resb 6
    v1    resb 4
    v2    resb 2
    ans   resb 4
    base  resb 8

    count resb 1

section .text
    global _start

_start:
    ; Check if processor is in protected mode
    SMSW ax
    BT ax, 0
    JC inProtection
    rw 1, m2, m2Len
    jmp cont

inProtection:
    rw 1, m1, m1Len

cont:
    ; GDTR
    rw 1, m3, m3Len
    SGDT [gdtrv]

    ; Print Limit
    rw 1, labelLimit, labelLimitLen
    movzx eax, word [gdtrv]
    mov word [v2], ax
    call htoa16
    rw 1, ans, 4
    rw 1, newLine, nL

    ; Print Base
    rw 1, labelBase, labelBaseLen
    mov eax, dword [gdtrv + 2]
    mov dword [v1], eax
    call htoa32
    rw 1, base, 8
    rw 1, newLine, nL

    ; IDTR
    rw 1, m4, m4Len
    SIDT [idtrv]

    ; Print Limit
    rw 1, labelLimit, labelLimitLen
    movzx eax, word [idtrv]
    mov word [v2], ax
    call htoa16
    rw 1, ans, 4
    rw 1, newLine, nL

    ; Print Base
    rw 1, labelBase, labelBaseLen
    mov eax, dword [idtrv + 2]
    mov dword [v1], eax
    call htoa32
    rw 1, base, 8
    rw 1, newLine, nL

    ; LDTR
    rw 1, m5, m5Len
    rw 1, labelValue, labelValueLen
    SLDT ax
    mov word [v2], ax
    call htoa16
    rw 1, ans, 4
    rw 1, newLine, nL

    ; TR
    rw 1, m6, m6Len
    rw 1, labelValue, labelValueLen
    STR ax
    mov word [v2], ax
    call htoa16
    rw 1, ans, 4
    rw 1, newLine, nL
	
    jmp exit

; -----------------------
; Convert 32-bit to ASCII hex
htoa32:
    mov eax, [v1]
    mov ebx, base
    mov byte [count], 8

.htoa32_loop:
    rol eax, 4
    mov dl, al
    and dl, 0Fh
    cmp dl, 9
    jle .lt9_32
    add dl, 7
.lt9_32:
    add dl, '0'
    mov [ebx], dl
    inc ebx
    dec byte [count]
    jnz .htoa32_loop
    ret

; -----------------------
; Convert 16-bit to ASCII hex
htoa16:
    mov ax, [v2]
    mov ebx, ans
    mov byte [count], 4

.htoa16_loop:
    rol ax, 4
    mov dl, al
    and dl, 0Fh
    cmp dl, 9
    jle .lt9_16
    add dl, 7
.lt9_16:
    add dl, '0'
    mov [ebx], dl
    inc ebx
    dec byte [count]
    jnz .htoa16_loop
    ret
    
    
    ; Exit syscall
    exit:
    mov rax, 60
    xor rdi, rdi
    syscall

