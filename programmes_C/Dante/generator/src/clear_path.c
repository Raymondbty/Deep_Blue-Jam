/*
** EPITECH PROJECT, 2022
** clear_path.c
** File description:
** make road
*/
#include "../include/generator.h"

void clear_path(char *line, int x)
{
    int a = 0;
    int pos = 0;
    int wall_state = 0;

    while ((wall_state = rand() % x) == 0);
    for (a = 0; a < wall_state; a = a + 1) {
        pos = rand() % x;
        line[pos] = '*';
    }
}

void clear_path_perfect(char *line, int x)
{
    int a = 0;
    int pos = 0;
    int wall_state = 0;

    while ((wall_state = rand() % x) == 0) {
        for (a = 0; a < wall_state; a = a + 1) {
            pos = rand() % x;
            line[pos] = '*';
        }
    }
}
