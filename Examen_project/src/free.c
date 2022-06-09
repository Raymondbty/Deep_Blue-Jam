/*
** EPITECH PROJECT, 2022
** free.c
** File description:
** free fucntion
*/
#include "my.h"

char *free_random(char **content)
{
    size_t size = 0;
    char *string;
    char *signal = NULL;

    srand(time(NULL));
    while (content[size])
        size = size + 1;
    if ((string = strdup(content[rand() % (size)])) == signal) {
        mr_clean_tab_bis(content);
        return signal;
    } else {
        mr_clean_tab_bis(content);
        return string;
    }
    return signal;
}
