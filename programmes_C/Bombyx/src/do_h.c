/*
** EPITECH PROJECT, 2021
** h.c
** File description:
** -h
*/
#include "../includes/my.h"

void do_h(void)
{
    my_putstr("USAGE");
    my_putchar('\n');
    my_putstr("    ./106bombyx n [k | i0 i1]\n");
    my_putchar('\n');
    my_putstr("DESCRIPTION\n");
    my_putstr("    n      number of first generation individuals\n");
    my_putstr("    k      growth rate from 1 to 4\n");
    my_putstr("    i0     initial generation (included)\n");
    my_putstr("    i1     final generation (included)\n");
}
