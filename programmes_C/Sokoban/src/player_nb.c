/*
** EPITECH PROJECT, 2022
** player_nb.c
** File description:
** verify there is only one player
*/
#include "../include/my.h"

int verify_1_player(soko_t *sokoban)
{
    int a = 0;
    int p = 0;

    while (sokoban->buffer[a] != 0) {
        if (sokoban->buffer[a] == 80) {
            p = p + 1;
            a = a + 1;
        } else {
            a = a + 1;
        }
    }
    if (p != 1) {
        return 84;
    }
    return 0;
}
