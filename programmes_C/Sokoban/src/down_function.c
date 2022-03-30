/*
** EPITECH PROJECT, 2022
** key_down.c
** File description:
** lol
*/
#include "../include/my.h"

void move_down(int pos_p, soko_t *sokoban)
{
    sokoban->buffer[pos_p] = 80;
    sokoban->buffer[sokoban->p_position] = 32;
    sokoban->p_position = pos_p;
    reload_map(sokoban);
}

int react_down(soko_t *sokoban)
{
    int pos_p = 0;

    pos_p = sokoban->p_position + sokoban->cols;
    if (sokoban->buffer[pos_p] == 32 || sokoban->buffer[pos_p] == 79) {
        move_down(pos_p, sokoban);
        verify_emacs_terminal(sokoban);
    } else if (sokoban->buffer[pos_p] == 88 &&
    (sokoban->buffer[pos_p + sokoban->cols] == 32
    || sokoban->buffer[pos_p + sokoban->cols] == 79)) {
        down_wall_handling(pos_p, sokoban);
        verify_emacs_terminal(sokoban);
    }
    verify_emacs_terminal(sokoban);
    return 0;
}
