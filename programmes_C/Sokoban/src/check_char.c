/*
** EPITECH PROJECT, 2022
** check_char.c
** File description:
** find X, ' ' etc
*/
#include "../include/my.h"

void check_nb_col_l(soko_t *sokoban)
{
    int a = 0;

    sokoban->cols = 0;
    sokoban->line = 0;

    while (sokoban->buffer[a] != 80) {
        a = a + 1;
    }
    sokoban->p_position = a;
    help_count_lc(sokoban);
}

void help_count_lc(soko_t *sokoban)
{
    int b = 0;
    int c = 0;

    while (sokoban->buffer[b] != 0) {
        b = b + 1;
    }
    while (sokoban->buffer[c] != 10) {
        sokoban->cols++;
        c = c + 1;
    }
    sokoban->cols = sokoban->cols + 1;
    sokoban->sz_map = b;
    sokoban->line = (b / sokoban->cols) + 1;
    check_nb_of_x(sokoban);
}

void check_nb_of_x(soko_t *sokoban)
{
    int a = 0;

    sokoban->p_position2 = sokoban->p_position;
    sokoban->buffer2 = malloc(sizeof(char) * 50000);
    for (a = 0; sokoban->buffer[a] != 0; a = a +1) {
        sokoban->buffer2[a] = sokoban->buffer[a];
    }
    sokoban->buffer2[a] = 0;
}
