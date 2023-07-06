/*
** EPITECH PROJECT, 2023
** list_other_flags.c
** File description:
** find others symbols flags
*/
#include "nm.h"

/*typedef struct d_flags {
    unsigned char stt;
    unsigned int sh_type;
    unsigned int sh_flags;
    char type;
} d_flags;
*/
static t_flags other_flags[] = {
    { STT_NOTYPE, SHT_PROGBITS, 0, 'n' },
    { STT_NOTYPE, SHT_PROGBITS, 2, 'r' },
    { STT_NOTYPE, SHT_PROGBITS, 50, 'r' },
    { STT_NOTYPE, SHT_PROGBITS, 3, 'd' },
    { STT_NOTYPE, SHT_PROGBITS, 6, 't' },
    { STT_NOTYPE, SHT_NOBITS, 3, 'b' },
    { STT_OBJECT, SHT_DYNAMIC, 3, 'd' },
    { STT_OBJECT, SHT_NOTE, 2, 'r' },
    { STT_OBJECT, SHT_FINI_ARRAY, 3, 't' },
    { STT_OBJECT, SHT_INIT_ARRAY, 3, 't' },
    { STT_OBJECT, SHT_PROGBITS, 0, 'n' },
    { STT_OBJECT, SHT_PROGBITS, 2, 'r' },
    { STT_OBJECT, SHT_PROGBITS, 50, 'r' },
    { STT_OBJECT, SHT_PROGBITS, 3, 'd' },
    { STT_OBJECT, SHT_NOBITS, 3, 'b' },
    { STT_FUNC, SHT_PROGBITS, 6, 't' },
    { STT_TLS, SHT_PROGBITS, 1027, 'd' },
    { STT_TLS, SHT_NOBITS, 1027, 'b' },
    { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

char list_other_flags(Elf32_Sym *symtab, Elf32_Shdr *shdr)
{
    unsigned int b = -1;
    static unsigned int lsize = sizeof(other_flags) / sizeof(*other_flags);

    if (ELF32_ST_BIND(symtab->st_info) != STB_LOCAL) {
        return NO_TYPE;
    }
    while (++b < lsize) {
        if (ELF32_ST_TYPE(symtab->st_info) != other_flags[b].stt) {
            continue;
        }
        if (shdr[symtab->st_shndx].sh_type != other_flags[b].sh_type) {
            continue;
        }
        if (shdr[symtab->st_shndx].sh_flags != other_flags[b].sh_flags) {
            continue;
        }
        return other_flags[b].type;
    }
    return NO_TYPE;
}
