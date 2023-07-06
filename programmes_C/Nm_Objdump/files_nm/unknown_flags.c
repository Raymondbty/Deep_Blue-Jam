/*
** EPITECH PROJECT, 2023
** unknown_flags.c
** File description:
** deal with no_type flags
*/
#include "nm.h"

char unknown_flags(Elf32_Sym *array_sim)
{
    char symtype = NO_TYPE;
    unsigned char link = ELF32_ST_BIND(array_sim->st_info);
    unsigned char type = ELF32_ST_TYPE(array_sim->st_info);
    Elf32_Word shndx = array_sim->st_shndx;
    const char types[] = { NO_TYPE, 'v', 'w', NO_TYPE, 'o' };
    const char links[] = { NO_TYPE, 'V', 'W', NO_TYPE, 'T' };
    const int index = (link << 2) | type;

    if (index >= 0 && index < 20) {
        symtype = shndx == SHN_UNDEF ?
            types[index] + ('a' - 'A') : links[index];
    }
    return symtype;
}
