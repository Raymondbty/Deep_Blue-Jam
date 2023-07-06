/*
** EPITECH PROJECT, 2023
** Get_symbol_type.c
** File description:
** read name dangit
*/
#include "nm.h"

/*typedef struct {
    uint8_t stt;
    uint32_t sh_type;
    uint64_t sh_flags;
    char type;
} SymbolTypeFlags;
*/
static SymbolTypeFlags mainflags[] = {
    { STT_NOTYPE, SHT_PROGBITS, 3, 'D' },
    { STT_OBJECT, SHT_PROGBITS, 3, 'D' },
    { STT_OBJECT, SHT_PROGBITS, 2, 'R' },
    { STT_OBJECT, SHT_NOBITS, 3, 'B' },
    { STT_FUNC, SHT_NULL, 0, 'U' },
    { STT_FUNC, SHT_PROGBITS, 6, 'T' },
    { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

char get_symbol_type(Elf32_Sym *symtab, Elf32_Shdr *shdr)
{
    size_t sz = 0;

    for (sz = 0; sz < sizeof(mainflags) / sizeof(mainflags[0]); sz++) {
        if (ELF32_ST_TYPE(symtab->st_info) == mainflags[sz].stt &&
            shdr[symtab->st_shndx].sh_type == mainflags[sz].sh_type &&
            shdr[symtab->st_shndx].sh_flags == mainflags[sz].sh_flags) {
            return (mainflags[sz].type);
        }
    }
    if (ELF32_ST_BIND(symtab->st_info) == STB_GLOBAL) {
        return ('U');
    }
    return (NO_TYPE);
}
