/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-mathieu.nowakowski
** File description:
** my_str_to_word_array.c
*/

#include "include.h"

int count_words(char *str, char *delim)
{
    int count = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == delim[0]) {
            count++;
        }
        i++;
    }
    return count + 1;
}

int len_word_delim(char *str, char *delim)
{
    int i = 0;

    while (str[i] != '\0' && str[i] != delim[0]) {
        i++;
    }
    return i;
}

char **my_str_to_word_array(char *str, char *delim)
{
    char **array;
    int nbr_words = count_words(str, delim);

;    if (str == NULL || delim == NULL)
        return NULL;
    array = malloc(sizeof(char *) * (nbr_words + 1));
    if (array == NULL)
        return NULL;
    for (int i = 0; i < nbr_words; i++) {
        if (*str != delim[0]) {
            array[i] = malloc(sizeof(char) * (len_word_delim(str, delim) + 1));
            strncpy(array[i], str, len_word_delim(str, delim));
            array[i][len_word_delim(str, delim)] = '\0';
            str += len_word_delim(str, delim);
        }
        str++;
    }
    array[nbr_words] = NULL;
    return array;
}

void free_word_array(char **array)
{
    if (array == NULL) {
        return;
    }
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
}
