/*
** EPITECH PROJECT, 2022
** display_clues.c
** File description:
** display_*
*/
#include "my.h"

char *display_clues(char *attempt, char *objective, char *game)
{
    size_t size = 0;
    int boucle = 0;
    char asterix = '*';
    char pointi = '?';

    for (boucle = 0; attempt[size] != '\0'; boucle++) {
        if (attempt[size] == objective[size]) {
            game[size] = attempt[size];
        } else if (place_clue_almost_right(objective, attempt[size], game)
== 3) {
            game[size] = pointi;
        } else {
            game[size] = asterix;
        }
        size = size + 1;
    }
    my_putstr(game);
    my_putstr("\n\n");
    return game;
}
