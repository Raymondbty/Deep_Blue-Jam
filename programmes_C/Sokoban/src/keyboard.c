/*
** EPITECH PROJECT, 2022
** keyboard_handling.c
** File description:
** lol
*/
#include "../include/my.h"

int handle_keyboard(soko_t *sokoban)
{
    while (win_condition(sokoban) == 2) {
        switch (getch()) {
        case 32://SPACE
            respawn(sokoban);
            break;
        case KEY_RIGHT:
            react_right(sokoban);
            break;
        case KEY_DOWN:
            react_down(sokoban);
            break;
        case KEY_LEFT:
            react_left(sokoban);
            break;
        case KEY_UP:
            react_up(sokoban);
        }
    }
    return 0;
}
