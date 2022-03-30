/*
** EPITECH PROJECT, 2022
** space_bar.c
** File description:
** lol
*/
#include "../include/my.h"

void reload_map(soko_t *sokoban)
{
    clear();
    change_o_for_x(sokoban);
    printw(sokoban->buffer);
    refresh();
}

void respawn(soko_t *sokoban)
{
    int a = 0;

    sokoban->p_position = sokoban->p_position2;
    for (a = 0; sokoban->buffer2[a] != 0; a = a +1) {
        sokoban->buffer[a] = sokoban->buffer2[a];
    }
    reload_map(sokoban);
}
