/*
** EPITECH PROJECT, 2022
** key_left
** File description:
** lol
*/
#include "../include/my.h"

int react_left(soko_t *sokoban)
{
    int pos_p = 0;

    pos_p = sokoban->p_position - 1;
    if (sokoban->buffer[pos_p] == 32 || sokoban->buffer[pos_p] == 79) {
        move_left(pos_p, sokoban);
        verify_emacs_terminal(sokoban);
    } else if (sokoban->buffer[pos_p] == 88 &&
    (sokoban->buffer[pos_p - 1] == 32
    || sokoban->buffer[pos_p - 1] == 79)) {
        left_wall_handling(pos_p, sokoban);
        verify_emacs_terminal(sokoban);
    }
    verify_emacs_terminal(sokoban);
    return 0;
}

void move_left(int pos_p, soko_t *sokoban)
{
    sokoban->buffer[pos_p] = 80;
    sokoban->buffer[sokoban->p_position] = 32;
    sokoban->p_position = pos_p;
    reload_map(sokoban);
}
