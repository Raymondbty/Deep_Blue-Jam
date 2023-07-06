; EPITECH PROJECT, 2023                                                         
; strncmp.asm                                                                    
; File description:                                                             
; Recreate strncmp in asm
[BITS 64]

global strncmp

    section .text

strncmp:
    MOV RCX, RDX
    REPZ CMPSB
    MOVZX EAX, BYTE [RDI + RCX - 1]
    MOVZX EDX, BYTE [RSI + RCX - 1]
    SUB EAX, EDX
    RET
