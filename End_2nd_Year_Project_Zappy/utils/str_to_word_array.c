/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-mathieu.nowakowski
** File description:
** my_str_to_word_array.c
*/

#include "include.h"

char **my_str_to_word_array(char *str, char *delim)
{
    char **array = malloc(sizeof(char *) * (strlen(str) + 1));
    char *token = strtok(str, delim);
    int i = 0;

    while (token != NULL) {
        array[i] = strdup(token);
        token = strtok(NULL, delim);
        i++;
    }
    array[i] = NULL;
    return array;
}
