/*
** EPITECH PROJECT, 2022
** back_value.c
** File description:
** return
*/
#include "../includes/my.h"

char back_value(char z)
{
    char Z;
    int a = 0;

    while (a < z)
        a++;
    Z = z - '0';
    return Z;
}
