/*
** EPITECH PROJECT, 2022
** wall_handling.c
** File description:
** read name
*/
#include "../include/my.h"

void up_wall_handling(int p_pos, soko_t *sokoban)
{
    sokoban->buffer[p_pos] = 80;
    sokoban->buffer[sokoban->p_position] = 32;
    sokoban->buffer[p_pos - sokoban->cols] = 88;
    sokoban->p_position = p_pos;
    reload_map(sokoban);
}

void left_wall_handling(int pos_p, soko_t *sokoban)
{
    sokoban->buffer[pos_p] = 80;
    sokoban->buffer[sokoban->p_position] = 32;
    sokoban->buffer[pos_p - 1] = 88;
    sokoban->p_position = pos_p;
    reload_map(sokoban);
}

void right_wall_handling(int pos_p, soko_t *sokoban)
{
    sokoban->buffer[pos_p] = 80;
    sokoban->buffer[sokoban->p_position] = 32;
    sokoban->buffer[pos_p + 1] = 88;
    sokoban->p_position = pos_p;
    reload_map(sokoban);
}

void down_wall_handling(int pos_p, soko_t *sokoban)
{
    sokoban->buffer[pos_p] = 80;
    sokoban->buffer[sokoban->p_position] = 32;
    sokoban->buffer[pos_p + sokoban->cols] = 88;
    sokoban->p_position = pos_p;
    reload_map(sokoban);
}
