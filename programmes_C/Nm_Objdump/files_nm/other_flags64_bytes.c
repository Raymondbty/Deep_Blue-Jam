/*
** EPITECH PROJECT, 2023
** all_other_flags64.c
** File description:
** list all other flags 64bytes
*/
#include "nm.h"

/*typedef struct all_other_flags {
    uint8_t stt;
    uint32_t sh_type;
    uint64_t sh_flags;
    char type;
} all_other_flags;*/

static all_other_flags other_flags[] = {
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

char other_flags64(Elf64_Sym *symbols_array, Elf64_Shdr *shdr)
{
    size_t t = 0;
    static const size_t size_flag = sizeof(other_flags)
        / sizeof(all_other_flags);

    if (ELF64_ST_BIND(symbols_array->st_info) != STB_LOCAL) {
        return (NO_TYPE);
    }
    for (t = 0; t < size_flag; ++t) {
        const all_other_flags *flag = &other_flags[t];
        if (ELF64_ST_TYPE(symbols_array->st_info) == flag->stt &&
            shdr[symbols_array->st_shndx].sh_type == flag->sh_type &&
            shdr[symbols_array->st_shndx].sh_flags == flag->sh_flags) {
            return flag->type;
        }
    }
    return (NO_TYPE);
}
