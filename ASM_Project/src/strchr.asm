; EPITECH PROJECT, 2023                                                         
; strchr.asm                                                                    
; File description:                                                             
; Recreate strchr in asm
[BITS 64]

global strchr

    section .text

strchr:
    MOV RAX, RDI
    MOV RCX, -1
    REP SCASB
    JNE .NOT_FOUND
    DEC RDI
    MOV RAX, RDI
    RET
.NOT_FOUND:
    XOR RAX, RAX
    RET
