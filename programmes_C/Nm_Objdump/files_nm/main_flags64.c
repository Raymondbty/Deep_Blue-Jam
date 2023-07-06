/*
** EPITECH PROJECT, 2023
** main_flags_bytes64.c
** File description:
** same as previous in 64mod
*/
#include "nm.h"

static t_flags main_fl[] = {
    { STT_NOTYPE, SHT_PROGBITS, 3, 'D' },
    { STT_OBJECT, SHT_PROGBITS, 3, 'D' },
    { STT_OBJECT, SHT_PROGBITS, 2, 'R' },
    { STT_OBJECT, SHT_NOBITS, 3, 'B' },
    { STT_FUNC, SHT_NULL, 0, 'U' },
    { STT_FUNC, SHT_PROGBITS, 6, 'T' },
    { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

char main_flags64(Elf64_Sym *arr_sym, Elf64_Shdr *shdr)
{
    unsigned int f = 0;
    static unsigned int	gsize = sizeof(main_fl)
        / sizeof(*main_fl);

    if (ELF64_ST_BIND(arr_sym->st_info) != STB_GLOBAL) {
        return (NO_TYPE);
    }
    for (f = 0; f < gsize; f++) {
        if (ELF64_ST_TYPE(arr_sym->st_info) != main_fl[f].stt)
            continue;
        if (shdr[arr_sym->st_shndx].sh_type != main_fl[f].sh_type)
            continue;
        if (shdr[arr_sym->st_shndx].sh_flags != main_fl[f].sh_flags)
            continue;
        return (main_fl[f].type);
    }
    return ('U');
}
