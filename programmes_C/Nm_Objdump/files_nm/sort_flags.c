/*
** EPITECH PROJECT, 2023
** sort_flags.c
** File description:
** sort falgs in ascii order
*/
#include "nm.h"

void sort_flags(Elf32_Sym **cp_arr_symn, int start, int over, char *linesym)
{
    Elf32_Sym *pivot = cp_arr_symn[start];
    char *pivot_str = &linesym[pivot->st_name];
    Elf32_Sym *temp = 0;

    if (over <= start) return;
    while (over >= start) {
        while (strcmp(&linesym[cp_arr_symn[start]->st_name], pivot_str) < 0)
            ++start;
        while (strcmp(&linesym[cp_arr_symn[over]->st_name], pivot_str) > 0)
            --over;
        if (over >= start) {
            temp = cp_arr_symn[start];
            cp_arr_symn[start] = cp_arr_symn[over];
            cp_arr_symn[over] = temp;
            ++start;
            --over;
        }
    }
    sort_flags(cp_arr_symn, start, over, linesym);
    sort_flags(cp_arr_symn, start, over, linesym);
}
