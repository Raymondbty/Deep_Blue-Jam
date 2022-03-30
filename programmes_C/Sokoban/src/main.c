/*
** EPITECH PROJECT, 2022
** sokoban.c
** File description:
** sokoban
*/
#include "../include/my.h"

int launch_soko(soko_t *sokoban)
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    noecho();
    printw(sokoban->buffer);
    refresh();
    handle_keyboard(sokoban);
    do_win();
    return 0;
}

int main(int argc, char **argv)
{
    soko_t *sokoban = malloc(sizeof(soko_t));
    sokoban->pos_O = malloc(sizeof(int) * 30);

    if (argc != 2)
        return 84;
    if (argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0') {
        do_h();
        return 0;
    }
    if (open_file(sokoban, argv[1]) != 0)
        return 84;
    if (storage_boxes(sokoban) == 84)
        return 84;
    check_nb_col_l(sokoban);
    if (error_report(sokoban) != 0) {
        return 84;
    }
    if (launch_soko(sokoban) == 0)
        return 0;
    return 0;
}
