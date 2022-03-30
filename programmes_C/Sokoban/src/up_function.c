/*
** EPITECH PROJECT, 2022
** key_up
** File description:
** lol
*/
#include "../include/my.h"

int react_up(soko_t *sokoban)
{
    int p_pos = 0;
    p_pos = sokoban->p_position - sokoban->cols;

    if (sokoban->buffer[p_pos] == 32 || sokoban->buffer[p_pos] == 79) {
        move_up(p_pos, sokoban);
        verify_emacs_terminal(sokoban);
    } else if (sokoban->buffer[p_pos] == 88 &&
    (sokoban->buffer[p_pos - sokoban->cols] == 32
    || sokoban->buffer[p_pos - sokoban->cols] == 79)) {
        up_wall_handling(p_pos, sokoban);
        verify_emacs_terminal(sokoban);
    }
    verify_emacs_terminal(sokoban);
    return 0;
}

void move_up(int p_pos, soko_t *sokoban)
{
    sokoban->buffer[p_pos] = 80;
    sokoban->buffer[sokoban->p_position] = 32;
    sokoban->p_position = p_pos;
    reload_map(sokoban);
}
