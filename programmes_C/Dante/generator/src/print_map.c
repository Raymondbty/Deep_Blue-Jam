/*
** EPITECH PROJECT, 2020
** dante
** File description:
** print map file
*/
#include "../include/generator.h"

void print_map(gen_t *gen)
{
    int a = 0;
    int size_line = line_size(gen);

    while (a < size_line) {
        printf("%s\n", gen->map[a]);
        a = a + 1;
        if (a + 1 == size_line - 1) {
            a++;
            printf("%s", gen->map[a]);
            printf("\n");
        }
    }
}

int line_size(gen_t *gen)
{
    int a = 0;

    while (gen->map[a] != NULL) {
        a = a + 1;
    }
    return a;
}
