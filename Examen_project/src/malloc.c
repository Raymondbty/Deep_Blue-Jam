/*
** EPITECH PROJECT, 2022
** malloc.c
** File description:
** malloc content
*/
#include "my.h"

char **help_malloc_content(char **content)
{
    char **array = NULL;
    size_t size = 0;
    char **nope = NULL;

    return malloc_content(content, array, size, nope);
}

char **malloc_content(char **content, char **array, size_t size, char **nope)
{
    if (content == nope) {
        if ((array = malloc(sizeof(char *) * 2)) == nope) {
            mr_clean_tab_bis(content);
            return nope;
        }
        array[1] = nope;
        return array;
    }
    for (; content[size] != nope; size = size + 1);
    if ((array = malloc(sizeof(char *) * (size + 2))) == nope)
        return nope;
    for (size = 0; content[size] != NULL; size = size + 1)
        if ((array[size] = strdup(content[size])) == nope) {
            mr_clean_tab_bis(content);
            return nope;
        }
    array[size + 1] = nope;
    mr_clean_tab_bis(content);
    return array;
}
