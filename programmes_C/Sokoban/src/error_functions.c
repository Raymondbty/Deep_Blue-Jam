/*
** EPITECH PROJECT, 2022
** error_functions.c
** File description:
** lol
*/
#include "../include/my.h"

int check_char(soko_t *sokoban)
{
    int a = 0;

    while (sokoban->buffer[a] != 0) {
        if (sokoban->buffer[a] != 32 && sokoban->buffer[a] != 35
            && sokoban->buffer[a] != 10 && sokoban->buffer[a] != 88
            && sokoban->buffer[a] != 79 && sokoban->buffer[a] != 80) {
            return 84;
        } else {
            a = a + 1;
        }
    }
    return 0;
}

int error_trap_square(soko_t *sokoban)
{
    int a = 0;
    int d = 0;
    int b = 0;

    b = sokoban->sz_map - sokoban->cols;
    while (d < sokoban->cols - 1) {
        if (sokoban->buffer[a] == 35 && sokoban->buffer[b] == 35) {
            d = d + 1;
            b = b + 1;
            a = a + 1;
        } else {
            return 84;
        }
    }
    return 0;
}
