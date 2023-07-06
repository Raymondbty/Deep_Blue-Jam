/*
** EPITECH PROJECT, 2023
** display_64results.c
** File description:
** in name
*/
#include "nm.h"

static Elf64_Sym **display_array64(Elf64_Sym *symtab, unsigned int size)
{
    unsigned int h = 0;
    Elf64_Sym **memory = malloc(sizeof(*memory) * (size + 1));
    if (memory == NULL) {
        fprintf(stderr, "error: malloc: failed.\n");
        return NULL;
    }
    for (h = 0; h < size; h++) {
        memory[h] = &symtab[h];
    }
    memory[size] = NULL;
    return (memory);
}

static void render_line64(Elf64_Sym **symtab_cpy,
    char *strsymtab, Elf64_Shdr *shdr, int l)
{
    char type = 'a';

    if (symtab_cpy[l]->st_name != 0 && symtab_cpy[l]->st_name
        != 1 && symtab_cpy[l]->st_info != STT_FILE) {
        type = search_for_flags64(symtab_cpy[l], shdr);
        if (type != 'U' && type != 'w') {
            printf("%016lx ", (unsigned long)symtab_cpy[l]->st_value);
        } else {
            printf("%17c", ' ');
        }
        printf("%c %s\n", type, &strsymtab[symtab_cpy[l]->st_name]);
    }
}

void display_64results(Elf64_Shdr *symsection, Elf64_Sym *symtab,
    char *strsymtab, Elf64_Shdr *shdr)
{
    unsigned int k = 0;
    unsigned int size = symsection->sh_size / sizeof(Elf64_Sym);
    Elf64_Sym **symtab_cpy = display_array64(symtab, size);
    if (symtab_cpy == NULL) {
        return;
    }
    sort_flags_64(symtab_cpy, 0, size - 1, strsymtab);
    for (k = 0; k < size; k++) {
        render_line64(symtab_cpy, strsymtab, shdr, k);
    }
    free(symtab_cpy);
}
