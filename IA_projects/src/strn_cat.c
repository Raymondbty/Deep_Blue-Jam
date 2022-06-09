/*
** EPITECH PROJECT, 2022
** strncat.c
** File description:
** lol
*/
#include <stddef.h>
#include "n4s.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int j = 0;

    while (dest[j] != '\0') {
        j++;
    }
    while (src[i] != '\0' && i < nb) {
        dest[j] = src[i];
        i++;
        j++;
    }
    dest[j] = '\0';
    return (dest);
}
