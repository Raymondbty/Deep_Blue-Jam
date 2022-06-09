/*
** EPITECH PROJECT, 2022
** clean_string.c
** File description:
** read
*/
#include "my.h"

void mr_clean_string(char *string)
{
    size_t size = 0;

    while (string[size] != '\0') {
        if (string[size] == '\n') {
            string[size] = '\0';
        }
        size = size + 1;
    }
}

void mr_clean_tab_bis(char **content)
{
    size_t size = 0;

    if (content == NULL) {
        return;
    }
    while (content[size] != NULL) {
        free(content[size]);
        size = size + 1;
    }
    free(content);
}

void mr_clean_tab(char **content)
{
    int a = 0;
    int b = 0;

    for (a = 0; content[a] != NULL; a = a + 1) {
        for (b = 0; content[a][b] != '\0'; b = b + 1) {
            (content[a][b] == '\n') ?  content[a][b] = '\0': content[a][b];
        }
    }
}
