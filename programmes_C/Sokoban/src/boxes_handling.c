/*
** EPITECH PROJECT, 2022
** error_functions2.c
** File description:
** lol
*/
#include "../include/my.h"

int storage_boxes(soko_t *sokoban)
{
    int position = 0;
    int a = 0;
    int box = 0;
    int o = 0;

    while (sokoban->buffer[a] != 0) {
        if (sokoban->buffer[a] == 88) {
            box = box + 1;
        } else if (sokoban->buffer[a] == 79) {
            o = o + 1;
            sokoban->pos_O[position] = a;
            position = position + 1;
        }
        a = a + 1;
    }
    if (box == 0 || box != o) {
        return 84;
    } else {
        return 0;
    }
}
