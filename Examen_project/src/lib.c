/*
** EPITECH PROJECT, 2022
** lib.c
** File description:
** lib function
*/
#include "my.h"
#include <unistd.h>

int my_strlen(char const *str)
{
    int a = 0;

    while (str[a] != '\0') {
        a++;
    }
    return (a);
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_putstr(char const *str)
{
    int a = 0;

    while (str[a] != '\0') {
        my_putchar(str[a]);
        a++;
    }
    return 0;
}
