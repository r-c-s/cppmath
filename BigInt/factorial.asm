global factorial
 
factorial: 
    push    rbp                   ; save base pointer
    push    rdi                   ; save function parameter
    mov     rcx, rsp              ; save stack pointer in rcx 
    mov     rsp, rdi              ; pointer to allocated array is the new stack pointer
    mov     rdi, [rsp]            ; first element of this array is the number
    mov     [rsp+8], rcx          ; save rcx which holds stack pointer
    mov     [rsp+16], rdi         ; first number in factorial
    mov     qword [rsp+24], -1    ; flag end of number
    add     rsp, 16               ; move behind flag
    mov     [rsp-16], rsp         ; save rsp
    mov     rbx, 100000000        ; we'll use this number to single out carries
                                  ; (only 8 digit numbers per register)
f_main_loop:
    cmp     rdi, 1                ; factorial is done computing?
    jle     f_exit                ; done with program
    dec     rdi                   ; else decrement parameter
    mov     rbp, [rsp-16]         ; copy of stack pointer
    xor     rdx, rdx              ; clear these registers
    xor     rcx, rcx              ; rcx will hold the carry
    
f_skip_zeroes:                    ; skips zeros since there's no point in multiplying them
    cmp     qword [rbp], 0        ; is this a zero?
    jne     f_save_rbp            ; if not, multiply
    add     rbp, 8                ; else move on to the next digit
    jmp     f_skip_zeroes         ; check again
    
f_save_rbp:
    mov     [rsp-16], rbp         ; save rbp since everything before it are zeros

f_multiply_loop:
    cmp     qword [rbp], -1       ; check for flag
    jne     f_ml_continue         ; no flag yet, multiply again
    cmp     rcx, 0                ; else check if there's a carry
    je      f_main_loop           ; no carry, back to main loop
    mov     rax, rcx              ; move carry to rax

f_ml_propagate_carry:             ; pushes each digit of carry
    xor     rdx, rdx              ; to the next stack location
    div     rbx                   ; divide carry, remaining carry goes back in rax 
    mov     [rbp], rdx            ; move remainder to current location
    add     rbp, 8                ; move to the next adress
    cmp     rax, 0                ; is there still a carry?
    jne     f_ml_propagate_carry  ; then do it again
    mov     qword [rbp], -1       ; else push flag back in before leaving
    jmp     f_main_loop           ; next

f_ml_continue:
    mov     rax, [rbp]            ; gets current value in stack address
    mul     rdi                   ; multiply it by factorial (n..1)
    add     rax, rcx              ; carry from previous multiplication
    div     rbx                   ; get only 1 digit
    mov     [rbp], rdx            ; move that digit to current stack address
    mov     rcx, rax              ; rcx holds the current carry
    add     rbp, 8                ; shift go to next stack
    jmp     f_multiply_loop       ; go back to multiply loop

f_exit:  
    mov     rsp, [rsp-8]          ; restore stack pointer and leaves allocated memory space
    pop     rax                   ; return value is same as parameter
    add     rax, 16
    pop     rbp                   ; restore base pointer
    ret 
