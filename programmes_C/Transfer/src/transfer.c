/*
** EPITECH PROJECT, 2022
** transfer.c
** File description:
** lol
*/
#include "../includes/my.h"

double do_transfer(int argc, char *argv, double A)
{
    double a = 0;
    int b = 0;
    int c = 0;
    int E = 1;

    c = strlen(argv) - E;
    for (c = c; c >= 0; c += -2) {
        for ( ; c >= 0 && argv[c] != '*'; c = c - 1);
        c = c + 1;
        a *= A;
        a += back_value(argv[c]);
    }
    return a;
}
