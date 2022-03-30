/*
** EPITECH PROJECT, 2022
** size_terminal.c
** File description:
** verify_size
*/
#include "../include/my.h"

void verify_emacs_terminal(soko_t *sokoban)
{
    int max_up = 0;
    int max_lenght = 0;

    getmaxyx(stdscr, max_up, max_lenght);
    if (max_up < sokoban->cols || max_lenght < sokoban->line - 1) {
        printw("Too small terminal, please make it bigger\n");
        exit(84);
    }
}
