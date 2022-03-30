/*
** EPITECH PROJECT, 2020
** dante
** File description:
** maze generator file
*/
#include "../include/generator.h"

int verify_surrounding(gen_t *gen, emp_t *emp)
{
    emp_t undone;
    undone.a = emp->a;
    undone.b = emp->b - 1;
    if (set_road(gen, &undone) &&
        check_tiles_wall(gen, &undone) == 1)
        return 1;
    undone.b = emp->b + 1;
    if (set_road(gen, &undone) &&
        check_tiles_wall(gen, &undone) == 1)
        return 1;
    undone.a = emp->a - 1;
    undone.b = emp->b;
    if (set_road(gen, &undone) &&
        check_tiles_wall(gen, &undone) == 1)
        return 1;
    undone.a = emp->a + 1;
    if (set_road(gen, &undone) &&
        check_tiles_wall(gen, &undone) == 1)
        return 1;
    return 0;
}

void line_selected(int a, gen_t *gen)
{
    int b = 0;

    for (b = 0; gen->map[a][b] != '\0'; b = b + 1) {
        if (gen->map[a][b] == 'X' && b != 0) {
            perfect_check_tiles_wall(a, b, gen);
        }
    }
}

int set_road(gen_t *gen, emp_t *emp)
{
    if (emp->a >= gen->y || emp->b >= gen->x || emp->b < 0 ||
        emp->a < 0) {
        return 0;
    }
    return 1;
}

int check_tiles_wall(gen_t *gen, emp_t *emp)
{
    int c = 0;

    if (emp->a >= 0 && emp->b - 1 >= 0 &&
        emp->a < gen->y && emp->b - 1 < gen->x &&
        gen->map[emp->b - 1][emp->a] != 88)
        c = c + 1;
    if (emp->a + 1 >= 0 && emp->b >= 0 &&
        emp->a + 1 < gen->y && emp->b < gen->x &&
        gen->map[emp->b][emp->a + 1] != 88)
        c = c + 1;
    if (emp->a >= 0 && emp->b + 1 >= 0 &&
        emp->a < gen->y && emp->b + 1 < gen->x &&
        gen->map[emp->b + 1][emp->a] != 88)
        c = c + 1;
    if (emp->a - 1 >= 0 && emp->b >= 0 &&
        emp->a - 1 < gen->y && emp->b < gen->x &&
        gen->map[emp->b][emp->a - 1] != 88)
        c = c + 1;
    return c;
}
