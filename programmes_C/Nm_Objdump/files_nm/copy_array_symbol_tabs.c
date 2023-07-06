/*
** EPITECH PROJECT, 2023
** render_symbols.c
** File description:
** print results
*/
#include "nm.h"

static void display_array(Elf32_Sym *sym, char *flag_array, Elf32_Shdr *shdr)
{
    char symtyp = search_for_flags(sym, shdr);

    if (sym->st_name && sym->st_name != 1 && sym->st_info != 4) {
        if (symtyp != 'U' && symtyp != 'w') {
            printf("%08x ", sym->st_value);
        } else {
            printf("%9c", ' ');
        }
        printf("%c %s\n", symtyp, &flag_array[sym->st_name]);
    }
}

static Elf32_Sym **copy_array_symbol_tabs(Elf32_Sym *flag_array,
                                            unsigned int size)
{
    unsigned int c = 0;
    Elf32_Sym **memory = malloc(sizeof(*memory) * size);

    if (!memory) {
        fprintf(stderr, "error: malloc: failed.\n");
        return NULL;
    }
    for (c = 0; c < size; c++) {
        memory[c] = &flag_array[c];
    }
    return (memory);
}

void render_symbols(Elf32_Shdr *symsection, Elf32_Sym *flag_array,
                    char *strsymtab, Elf32_Shdr *shdr)
{
    unsigned int d = 0;
    unsigned int size = symsection->sh_size / sizeof(*flag_array);
    Elf32_Sym **symtab_cpy = copy_array_symbol_tabs(flag_array, size);

    if (!symtab_cpy) {
        return;
    }
    sort_flags(symtab_cpy, 0, size - 1, strsymtab);
    for (d = 0; d < size; d++)
        display_array(symtab_cpy[d], strsymtab, shdr);
    free(symtab_cpy);
}
