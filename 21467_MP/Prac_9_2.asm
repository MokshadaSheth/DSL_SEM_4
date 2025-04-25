%macro scall 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

    
section .data
    extern msg6, len6, scount, ncount, chacount, new, new_len

section .bss
    extern buffer, cnt, cnt2, cnt3

section .text
 global spaces, enters, occ


; ---------------------------------------
; Procedure: spaces
; Counts number of spaces in buffer
; Output: scount holds count as ASCII
spaces:
    mov rsi, buffer

.next_space:
    mov al, [rsi]
    cmp al, 0
    je .end_space
    cmp al, 0x20         ; space
    je .inc_space
    inc rsi
    dec byte[cnt]
    jnz .next_space
    jmp .end_space

.inc_space:
    inc byte[scount]
    inc rsi
    dec byte[cnt]
    jnz .next_space

.end_space:
    add byte[scount], '0'
    scall 1, 1, scount, 2
    scall 1, 1, new, new_len
    ret

; ---------------------------------------
; Procedure: enters
; Counts number of newline characters
; Output: ncount holds count as ASCII
enters:
    mov rsi, buffer

.next_enter:
    mov al, [rsi]
    cmp al, 0
    je .end_enter
    cmp al, 0x0A         ; newline
    je .inc_enter
    inc rsi
    dec byte[cnt2]
    jnz .next_enter
    jmp .end_enter

.inc_enter:
    inc byte[ncount]
    inc rsi
    dec byte[cnt2]
    jnz .next_enter

.end_enter:
    add byte[ncount], '0'
    scall 1, 1, ncount, 2
    scall 1, 1, new, new_len
    ret

; ---------------------------------------
; Procedure: occ
; Counts occurrences of character in BL
; Output: chacount holds count as ASCII
occ:
    mov rsi, buffer

.next_occ:
    mov al, [rsi]
    cmp al, 0
    je .end_occ
    cmp al, bl
    je .inc_occ
    inc rsi
    dec byte[cnt3]
    jnz .next_occ
    jmp .end_occ

.inc_occ:
    inc byte[chacount]
    inc rsi
    dec byte[cnt3]
    jnz .next_occ

.end_occ:
    add byte[chacount], '0'
    scall 1, 1, msg6, len6
    scall 1, 1, chacount, 1
    scall 1, 1, new, new_len
    ret

