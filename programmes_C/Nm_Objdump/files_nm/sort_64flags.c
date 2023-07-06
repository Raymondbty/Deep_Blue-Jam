/*
** EPITECH PROJECT, 2023
** sort_flags_64.c
** File description:
** read name
*/
#include "nm.h"

static void swap_ptrs(Elf64_Sym **symtab_cpy, int i, int j)
{
    Elf64_Sym *temp = symtab_cpy[i];

    symtab_cpy[i] = symtab_cpy[j];
    symtab_cpy[j] = temp;
}

void sort_flags_64(Elf64_Sym **symtab_cpy, int start, int end, char *strsymtab)
{
    int pivot_index = start;
    int g = 0;

    if (start >= end) return;
    char *pivot_str = &strsymtab[symtab_cpy[pivot_index]->st_name];
    for (g = start + 1; g <= end; g++) {
        char *curr_str = &strsymtab[symtab_cpy[g]->st_name];
        if (strcmp(curr_str, pivot_str) < 0) {
            pivot_index++;
            swap_ptrs(symtab_cpy, pivot_index, g);
        }
    }
    swap_ptrs(symtab_cpy, start, pivot_index);
    sort_flags_64(symtab_cpy, start, pivot_index - 1, strsymtab);
    sort_flags_64(symtab_cpy, pivot_index + 1, end, strsymtab);
}
