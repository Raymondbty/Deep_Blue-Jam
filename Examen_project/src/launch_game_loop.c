/*
** EPITECH PROJECT, 2022
** launch_game_loop.c
** File description:
** read name
*/
#include "my.h"

int launch_game_loop(char *word, char *game)
{
    char *attempt = NULL;
    int loop = 0;
    char *back_value = NULL;

    for (loop = 0; (attempt = error_handling_take_input(word)) == back_value;
loop++);
    game = display_clues(attempt, word, game);
    if (strcmp(game, word) == 0) {
        loop_free(attempt);
        loop_free(game);
        return 2;
    }
    loop_free(attempt);
    loop_free(game);
    return 0;
}

int loop_free(char *loop)
{
    free(loop);
    return 0;
}
