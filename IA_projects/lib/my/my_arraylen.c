/*
** EPITECH PROJECT, 2022
** my_arraylen.c
** File description:
** calculate the length of an array of strings
*/
#include <unistd.h>

int my_arraylen(char const **array)
{
    int i = 0;

    while (array[i] != NULL) {
        ++i;
    }
    return (i);
}
