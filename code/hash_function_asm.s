;-------------------------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||HASH FUNCTION|||||||||||||||||||||||||||||||||||||||||||||
;-------------------------------------------------------------------------------------------------
;   trollohash (stdcall) - it can call from C-program            
;-------------------------------------------------------------------------------------------------
;   Needs:                  handled line in rdi, args (stack format)
;                                               rdi, rsi, rdx, rcx, r8, r9 + stack using
;                                                1    2    3    4    5   6...   
; 
;   Return:                 none
;   Destroy list:           rax, rbx, rcx, rdx, rdi, rsi, r8, r9
;-------------------------------------------------------------------------------------------------

section .text
global _trollohash

_trollohash:  
            ;PROLOGUE																																																												
            push rbp								 	
            mov rbp, rsp
            push rbx
                                                ; rdi - ptr to curr str 
            xor r11, r11
            mov rbx, 1001
            mov rcx, 1

.next:      xor rax, rax
            mov al, byte [rdi]
            cmp al, 0
            je .end

            mul rcx
            add r11, rax

            mov rax, rcx
            mul rbx
            mov rcx, rax
            inc rdi

            jmp .next

.end:
            ;EPILOGUE
            mov rax, r11
            mov rbx, qword [rbp - 8]

            mov rsp, rbp                        ; skip local data
            pop rbp

            ret

;-------------------------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-------------------------------------------------------------------------------------------------