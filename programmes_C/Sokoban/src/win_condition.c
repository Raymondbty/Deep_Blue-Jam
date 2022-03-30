/*
** EPITECH PROJECT, 2022
** check_win.c
** File description:
** lol
*/
#include "../include/my.h"

int win_condition(soko_t *sokoban)
{
    int a = 0;
    int b = 0;

    while (sokoban->buffer[a] != 0) {
        if (a == sokoban->pos_O[b]) {
            if (sokoban->buffer[sokoban->pos_O[b]] == 'X') {
                b = b + 1;
            } else {
                return 2;
            }
        }
        a = a + 1;
    }
    return 0;
}

void do_win(void)
{
    refresh();
    endwin();
    exit(0);
}
