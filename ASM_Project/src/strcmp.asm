; EPITECH PROJECT, 2023                                                         
; strcmp.asm                                                                    
; File description:                                                             
; Recreate strcmp in asm
[BITS 64]

global strcmp

    section .text

strcmp: 
    MOV RAX, RDI
    MOV RSI, RSI
    MOV RCX, -1
    REP CMPSB
    MOVZX EAX, AL
    SUB EAX, 1
    RET
