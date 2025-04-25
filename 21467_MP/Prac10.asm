%macro print 2
    mov rax, 01
    mov rdi, 01
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

%macro exit 0
    mov rax, 60
    xor rdi, rdi
    syscall
%endmacro

section .bss
    arg_input     resb 1        ; Store input digit
    result_ascii  resb 4        ; Store hex output (up to 4 digits)
    factorial_val resd 1        ; 4 bytes to store result of factorial

section .data
    newline db 0xA

section .text
global _start

_start:
    ; Step 1: Get command-line argument
    pop rbx                ; argc
    pop rbx                ; argv[0]
    pop rbx                ; argv[1] (pointer to input string)

    mov al, [rbx]          ; first character (digit char like '5')
    sub al, '0'            ; convert ASCII to number
    mov [arg_input], al

    ; Step 2: Print the input digit (as ASCII again)
    add al, '0'            ; back to ASCII
    mov [arg_input], al
    print arg_input, 1
    print newline, 1

    ; Step 3: Calculate factorial
    sub al, '0'            ; convert to number again
    movzx ecx, al          ; move into ecx for loop counter
    call factorial
    mov [factorial_val], eax  ; store full 4-byte result

    ; Step 4: Convert factorial result to ASCII (hex)
    mov eax, [factorial_val]
    mov esi, eax           ; move to esi for hex conversion
    call hex_to_ascii

    ; Step 5: Print final result
    print result_ascii, 4
    print newline, 1

    exit

factorial:
    mov eax, 1
.loop:
    test ecx, ecx
    jz .done
    mul ecx
    dec ecx
    jmp .loop
.done:
    ret

hex_to_ascii:
    mov ebx, esi           ; get result value in ebx
    mov rdi, result_ascii
    mov rcx, 4             ; convert 4 nibbles

.convert_loop:
    rol ebx, 4             ; rotate left by 4 to get highest nibble first
    mov dl, bl
    and dl, 0x0F           ; isolate the nibble
    cmp dl, 9
    jbe .add30
    add dl, 7
.add30:
    add dl, '0'
    mov [rdi], dl
    inc rdi
    loop .convert_loop
    ret

