/*
** EPITECH PROJECT, 2022
** load_imp_maze.c
** File description:
** design imp maze
*/
#include "../include/generator.h"

void move_forward(gen_t *gen, emp_t *emp)
{
    emp_t move;
    int up = rand() % gen->modulo;
    int down = (rand() % gen->modulo) * gen->modulo - 1;

    move.a = emp->a;
    move.b = emp->b;
    if (up == 0)
        emp->b = emp->b + down;
    else
        emp->a = emp->a + up;
    while (set_road(gen, emp) == 0 || check_tiles_wall(gen, emp) > 1 ||
gen->map[emp->b][emp->a] == 42) {
        emp->a = move.a;
        emp->b = move.b;
        up = rand() % gen->modulo;
        down = (rand() % gen->modulo) * gen->modulo - 1;
        if (up == 0)
            emp->b = emp->b + down;
        else
            emp->a = emp->a + down;
    }
}

char **load_maze(int x, int y, gen_t *gen)
{
    int a = 0;
    int b = 0;

    while (a < y) {
        gen->map[a] = malloc(sizeof(char) * (x + 1));
        a = a + 1;
    }
    gen->map[a] = NULL;
    for (b = 0; gen->map[b] != NULL; b = b + 1) {
        if (b == 0) {
            load_line_1(gen->map[b], x);
        } else {
            load_all_lines(gen->map[b], x);
        }
    }
    return gen->map;
}

void load_all_lines(char *line, int x)
{
    int a = 0;

    while (a < x - 1) {
        line[a] = 'X';
        a = a + 1;
    }
    line[a] = '*';
    line[a + 1] = '\0';
}

void load_line_1(char *line, int x)
{
    int a = 0;

    while (a < x) {
        line[a] = '*';
        a = a + 1;
    }
    line[a] = '\0';
}
