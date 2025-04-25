

%macro scall 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

global buffer, cnt, cnt2, cnt3
global scount, ncount, chacount
global msg6, len6, new, new_len


section .data
    filename     db "input.txt", 0
    msg1         db "Enter character to search: ", 0
    msg1_len     equ $ - msg1

    msg6         db "Character Occurrence: ", 0
    len6         equ $ - msg6

    new          db 10
    new_len      equ 1

section .bss
    buffer       resb 1024
    char_in      resb 1

    cnt          resb 1
    cnt2         resb 1
    cnt3         resb 1

    scount       resb 1
    ncount       resb 1
    chacount     resb 1

section .text
    global  _start
    extern spaces, enters, occ

_start:
    ; Print message to enter char
    scall 1, 1, msg1, msg1_len

    ; Read one byte from user (char_in)
    scall 0, 0, char_in, 1

    ; Open the file input.txt
    mov rax, 2              ; sys_open
    mov rdi, filename
    mov rsi, 0              ; O_RDONLY
    syscall
    mov r12, rax            ; save file descriptor

    ; Read file into buffer
    scall 0, r12, buffer, 1024
    mov r13, rax            ; bytes read

    ; Initialize counters
    mov byte[cnt], r13b
    mov byte[cnt2], r13b
    mov byte[cnt3], r13b

    mov byte[scount], 0
    mov byte[ncount], 0
    mov byte[chacount], 0

    ; Call spaces
    call spaces

    ; Call enters
    call enters

    ; Move char_in to bl for occ
    mov bl, byte[char_in]

    ; Call occ
    call occ

    ; Exit
    mov rax, 60
    xor rdi, rdi
    syscall

