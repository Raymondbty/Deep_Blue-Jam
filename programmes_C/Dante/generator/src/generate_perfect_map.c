/*
** EPITECH PROJECT, 2022
** generate_perfect_map.c
** File description:
** read name
*/
#include "../include/generator.h"

char **generate_perfect_map(char **argv, gen_t *gen)
{
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    gen->map = make_perfect(x, y, gen);
    perfect_verify_surrounding(y, gen);
    return gen->map;
}

void perfect_verify_surrounding(int y, gen_t *gen)
{
    int a = 0;

    for (a = 1; a < y - 1; a = a + 1) {
        line_selected(a, gen);
    }
}

void perfect_check_tiles_wall(int a, int b, gen_t *gen)
{
    if (gen->map[a][b + 1] == '*' && gen->map[a][b - 1] == '*'
    && (gen->map[a - 1][b - 1] != '*'
    || gen->map[a - 1][b + 1] != '*' ||
    gen->map[a + 1][b - 1] != '*'
    || gen->map[a + 1][b + 1] != '*')) {
        gen->map[a][b] = '*';
    } else if (gen->map[a - 1][b] == '*' && gen->map[a + 1][b] == '*' &&
    (gen->map[a - 1][b - 1] != '*'
    || gen->map[a - 1][b + 1] != '*' ||
    gen->map[a + 1][b - 1] != '*'
    || gen->map[a + 1][b + 1] != '*')) {
        gen->map[a][b] = '*';
    }
}

char **make_perfect(int x, int y, gen_t *gen)
{
    int a = 0;
    int b = x / 2;

    gen->map = malloc(sizeof(char *) * (y + 1));
    gen->map = load_maze(x, y, gen);

    for (a = 1; gen->map[a] != NULL; a = a + 1) {
        if (a % 2 == 0) {
            clear_path_perfect(gen->map[a], x);
        } else {
            clear_path_perfect(gen->map[a], b);
        }
    }
    return gen->map;
}
