; EPITECH PROJECT, 2023
; memcpy.asm
; File description:
; Recreate memcpy in asm
[BITS 64]

global memcpy

    section .text

memcpy:
    PUSH RBP
    MOV RBP, RSP
    MOV RDI, [RBP + 16]
    MOV RSI, [RBP + 24]
    MOV RCX, [RBP + 32]
    REP MOVSB
    POP RBP
    RET
