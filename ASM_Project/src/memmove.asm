; EPITECH PROJECT, 2023
; memmove.asm
; File description:
; Recreate memmove in asm
[BITS 64]
    
global memmove

    section .text

memmove:
    CMP RDI, RSI
    JAE .FORWARD
    LEA RSI, [RSI+RDX-1]
    LEA RDI, [RDI+RDX-1]
    STD
.FORWARD:
    MOV RCX, RDX
    REP MOVSB
    CLD
    RET
