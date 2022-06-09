/*
** EPITECH PROJECT, 2022
** take_input.c
** File description:
** take the input from terminal
*/
#include "my.h"

char *error_handling_take_input(char *word)
{
    char *attempt = NULL;
    size_t size = 0;
    char *nope = NULL;

    my_putstr(">");
    getline(&attempt, &size, stdin);
    mr_clean_string(attempt);
    if (my_strlen(attempt) < my_strlen(word)) {
        my_putstr("Word too short. Retry.\n");
        loop_free(attempt);
        return nope;
    } else if (my_strlen(attempt) > my_strlen(word)) {
        my_putstr("Word too long. Retry.\n");
        loop_free(attempt);
        return nope;
    } else {
        return attempt;
    }
}
