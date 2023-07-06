/*
** EPITECH PROJECT, 2023
** unknown_flags64.c
** File description:
** do the same but with 64 modifs
*/
#include "nm.h"

char unknown_flags64(Elf64_Sym *flag_array)
{
    char type_of_flag = NO_TYPE;

    if (ELF64_ST_BIND(flag_array->st_info) == STB_WEAK) {
        if (ELF64_ST_TYPE(flag_array->st_info) == STT_OBJECT) {
            type_of_flag = (flag_array->st_shndx != SHN_UNDEF) ? 'V' : 'v';
        } else {
            type_of_flag = (flag_array->st_shndx != SHN_UNDEF) ? 'W' : 'w';
        }
    }
    return (type_of_flag);
}
