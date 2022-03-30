/*
** EPITECH PROJECT, 2020
** dante
** File description:
** maze generator main file
*/
#include "../include/generator.h"

int do_h(char **argv)
{
    if (argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0') {
        printf("Generate a maze perfect or imperfect, ");
        printf("required 3 or 4 arguments\n");
    } else {
        return 84;
    }
    return 0;
}

int support_main(int argc, char **argv, gen_t *gen)
{
    if (argc == 3) {
        if ((set_maze(gen)) == -1)
            return 84;
        else
            generate_imperfect_map(gen);
    } else if (argc == 4) {
        gen->map = generate_perfect_map(argv, gen);
    }
    print_map(gen);
    free_maze(gen);
    return 0;
}

int main(int argc, char **argv)
{
    gen_t *gen = malloc(sizeof(gen_t));

    if (argc < 2 || argc > 4) {
        return 84;
    }
    gen->x = atoi(argv[1]);
    gen->y = atoi(argv[2]);
    gen->map = NULL;
    if (argc == 2) {
        do_h(argv);
    }
    if (check_args(argc, argv) == 1 || atoi(argv[1]) == 0
    || atoi(argv[2]) == 0) {
        return 84;
    }
    return support_main(argc, argv, gen);
}

void free_maze(gen_t *gen)
{
    int a = 0;

    while (a < gen->x)
        free(gen->map[a++]);
    free(gen->map);
}
