; EPITECH PROJECT, 2023
; memset.asm
; File description:
; Recreate memset in asm
[BITS 64]

global memset

    section .text

memset:
    PUSH RBP
    MOV RBP, RSP
    MOV RDI, [RBP + 16]
    MOV AL, [RBP + 24]
    MOV RCX, [RBP + 32]
    CLD
    REP STOSB
    POP RBP
    RET
