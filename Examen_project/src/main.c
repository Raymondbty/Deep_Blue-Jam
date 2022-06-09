/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/
#include "my.h"

int main(int argc, char **argv)
{
    char *objective = NULL;
    char *game = NULL;

    help_main(argc, argv, objective, game);
}

int help_main(int argc, char **argv, char *objective, char *game)
{
    size_t size;
    size_t hidden = 0;

    if (verify_arg(argc) == 84)
        return 84;
    if ((objective = help_take_file(argv[1])) == NULL)
        return 84;
    size = my_strlen(objective);
    if ((game = malloc(sizeof(char) * (size + 1))) == NULL)
        return 84;
    game[size] = '\0';
    while (hidden != size) {
        game[hidden] = '*';
        hidden = hidden + 1;
    }
    if (help_initialize_lingo(objective, game) == 84)
        return 84;
    loop_free(objective);
    loop_free(game);
    return 0;
}

int verify_arg(int argc)
{
    if (argc != 2) {
        return 84;
    }
    return 0;
}
