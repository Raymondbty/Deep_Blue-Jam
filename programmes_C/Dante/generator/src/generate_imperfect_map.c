/*
** EPITECH PROJECT, 2022
** generate_perfect_map.c
** File description:
** read name
*/
#include "../include/generator.h"

void make_imperfect(gen_t *gen, emp_t *new)
{
    emp_t emp;

    srand(time(NULL));
    emp.a = new->a;
    emp.b = new->b;

    while ((emp.b == 0 && emp.a == 0) ||
           ((verify_surrounding(gen, &emp)) == 1 &&
            (emp.b != gen->x - 1 && emp.a != gen->y - 1))) {
        move_forward(gen, &emp);
        gen->map[emp.b][emp.a] = 42;
    }
}

void generate_imperfect_map(gen_t *gen)
{
    emp_t emp;

    emp.b = 0;
    for (; emp.b < gen->x; emp.b = emp.b + 1) {
        emp.a = 0;
        for (; emp.a < gen->y; emp.a = emp.a + 1) {
            if ((emp.b == 0 && emp.a == 0) ||
                (gen->map[emp.b][emp.a] == 88 &&
                 ((check_tiles_wall(gen, &emp) == 1) ||
                  (check_tiles_wall(gen, &emp) == 2)))) {
                gen->map[emp.b][emp.a] = 42;
                make_imperfect(gen, &emp);
            }
        }
    }
}

int set_maze(gen_t *gen)
{
    int a = 0;

    gen->modulo = 2;
    gen->up = rand() % gen->modulo;
    gen->down = (rand() % gen->modulo) * gen->modulo - 1;
    if ((gen->map = malloc(sizeof(char*) * gen->x)) == NULL) {
        return 0;
    }
    while (a < gen->x) {
        gen->map[a] = malloc(sizeof(char) * gen->y + 1);
        memset(gen->map[a], 88, gen->y);
        gen->map[a][gen->y] = '\0';
        a = a + 1;
    }
    return 1;
}
