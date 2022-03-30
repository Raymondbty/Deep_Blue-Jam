/*
** EPITECH PROJECT, 2021
** my_putstr.c
** File description:
** display 1by1 the character of a string
*/
#include <unistd.h>

void my_putchar(char c);

int my_putstr(char const *str)
{
    int a = 0;

    while (str[a] != '\0') {
        my_putchar(str[a]);
        a++;
    }
}
