/*
** EPITECH PROJECT, 2022
** my_strlen.c
** File description:
** lol
*/
#include "n4s.h"

int my_strlen(char const *str)
{
    int a = 0;
    while (str[a] != '\0') {
        a++;
    }
    return (a);
}
