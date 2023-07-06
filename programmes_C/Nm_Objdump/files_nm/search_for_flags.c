/*
** EPITECH PROJECT, 2023
** search_flags.c
** File description:
** search for flags
*/
#include "nm.h"

char search_for_flags(Elf32_Sym *flag_array, Elf32_Shdr *shdr)
{
    char type = NO_TYPE;
    switch (ELF32_ST_BIND(flag_array->st_info)) {
        case STB_GLOBAL:
            type = (ELF32_ST_TYPE(flag_array->st_info) == STT_OBJECT
    && flag_array->st_shndx == SHN_COMMON) ? 'C' : type;
            break;
        case STB_GNU_UNIQUE:
            type = 'U';
            break;
        case STB_LOCAL:
            type = (flag_array->st_shndx == SHN_ABS) ? 'a' :
            get_symbol_type(flag_array, shdr);
            break;
    }
    return type == NO_TYPE ? (list_other_flags(flag_array, shdr)
    == NO_TYPE ? unknown_flags(flag_array)
    : list_other_flags(flag_array, shdr)) : type;
}
