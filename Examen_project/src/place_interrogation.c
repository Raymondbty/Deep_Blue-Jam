/*
** EPITECH PROJECT, 2022
** place_interrogation.c
** File description:
** read
*/
#include "my.h"

int place_clue_almost_right(char *word, char chara, char *game)
{
    int point = 0;
    size_t size = 0;
    size_t size2 = 0;

    while (game[size] != '\0') {
        if (word[size] == chara && game[size] != chara) {
            point = point + 1;
        }
        size = size + 1;
    }
    while (word[size2] != '\0') {
        if (word[size2] == chara && point != 0)
            return 3;
        size2 = size2 + 1;
    }
    return 0;
}
