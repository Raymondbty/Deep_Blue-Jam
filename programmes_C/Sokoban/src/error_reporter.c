/*
** EPITECH PROJECT, 2022
** error_handling.c
** File description:
** lol
*/
#include "../include/my.h"

int error_report(soko_t *sokoban)
{
    int error = 0;

    error = error + error_trap_square(sokoban);
    error = error + check_char(sokoban);
    error = error + verify_1_player(sokoban);
    return error;
}
