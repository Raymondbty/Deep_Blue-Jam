/*
** EPITECH PROJECT, 2023
** seach_for_flags64.c
** File description:
** same but with ELF64
*/
#include "nm.h"

char search_for_flags64(Elf64_Sym *symbols_array, Elf64_Shdr *shdr)
{
    char type = 'a';

    if (ELF64_ST_BIND(symbols_array->st_info) == STB_GLOBAL
        && ELF64_ST_TYPE(symbols_array->st_info) == STT_OBJECT
        && symbols_array->st_shndx == SHN_COMMON)
        return 'C';
    if (ELF64_ST_BIND(symbols_array->st_info) == STB_GNU_UNIQUE)
        return 'U';
    if (symbols_array->st_shndx != SHN_ABS
        && symbols_array->st_shndx != SHN_COMMON) {
        if ((type = main_flags64(symbols_array, shdr)) != NO_TYPE ||
            (type = other_flags64(symbols_array, shdr)) != NO_TYPE)
            return (type);
    }
    if (unknown_flags64(symbols_array) != NO_TYPE)
        return (unknown_flags64(symbols_array));
    return (symbols_array->st_shndx == SHN_ABS
            && ELF64_ST_BIND(symbols_array->st_info) == STB_LOCAL) ? 'a' :
        (symbols_array->st_shndx == SHN_ABS) ? 'A' : '?';
}
