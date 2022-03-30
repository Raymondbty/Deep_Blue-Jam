/*
** EPITECH PROJECT, 2022
** replace_storage.c
** File description:
** lol
*/
#include "../include/my.h"

void change_o_for_x(soko_t *sokoban)
{
    int a = 0;
    int b = 0;

    while (sokoban->buffer[a] != 0) {
        if (a == sokoban->pos_O[b] &&
    sokoban->buffer[a] == 32) {
            sokoban->buffer[sokoban->pos_O[b]] = 79;
            b = b + 1;
        }
        a = a + 1;
    }
}
