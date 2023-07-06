; EPITECH PROJECT, 2023                                                         
; strlen.asm                                                                    
; File description:                                                             
; Recreate strlen in asm
[BITS 64]

global strlen:

    section .text

strlen:
	XOR RAX, RAX

count:
    CMP BYTE [RDI], 0
	JE end
	INC RDI
	INC RAX
	JMP count

end:
	RET
