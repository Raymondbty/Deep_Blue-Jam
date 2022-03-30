/*
** EPITECH PROJECT, 2022
** do_h.c
** File description:
** h flag
*/
#include "../include/my.h"

void do_h(void)
{
    my_putstr("USAGE");
    my_putchar('\n');
    my_putstr("     ./my_sokoban map\n");
    my_putstr("DECRIPTION\n");
    my_putstr("    map   file representing the warehouse map,");
    my_putstr(" containing '#' for walls,\n");
    my_putstr("          'P' for the player, 'X' for boxes and ");
    my_putstr("'O' for storage locations.\n");
}
