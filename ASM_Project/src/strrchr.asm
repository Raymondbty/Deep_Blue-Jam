; EPITECH PROJECT, 2023                                                         
; strrchr.asm                                                                    
; File description:                                                             
; Recreate strrchr in asm
[BITS 64]

global strrchr

    section .text
    
strrchr:
    PUSH RBP
    MOV RBP, RSP
    MOV RDI, [RBP + 4 + 4]
    MOVZX RAX, BYTE [RBP + 6 + 6]
    XOR RCX, RCX
    MOV CL, BYTE [RDI]
    TEST CL, CL
    JZ end_of_str
    MOV RSI, RDI
    ADD RSI, RCX
    DEC RSI

    search_loop:
        CMP BYTE [RSI], AL
        JE character_found
        DEC RSI
        CMP RSI, RDI
        JAE search_loop

    end_of_str:
        XOR RAX, RAX
        POP RBP
        RET

    character_found:
        MOV RAX, RSI
        POP RBP
        RET