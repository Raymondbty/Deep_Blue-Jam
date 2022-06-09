/*
** EPITECH PROJECT, 2022
** initialize_lingo.c
** File description:
** read name
*/
#include "my.h"

void print_start(void)
{
    my_putstr("*: invalid letter\n");
    my_putstr("?: incorrectly placed letter\n");
    my_putstr("Will you find the secret word?\n");
}

int help_initialize_lingo(char *objective, char *game)
{
    size_t size = 0;
    char *copy = NULL;

    return initialize_lingo(objective, game, size, copy);
}

int print_some_lingo(size_t size2)
{
    my_putstr("Round ");
    my_put_nbr((int)size2);
    my_putstr("\n");
}

int initialize_lingo(char *objective, char *game, size_t size, char *copy)
{
    size_t size2 = 1;

    print_start();
    while (size < strlen(objective)) {
        size == 0 ? my_putchar(objective[size]) : my_putchar('*');
        size = size + 1;
    }
    my_putstr("\n\n");
    while (size2 <= strlen(objective)) {
        if ((copy = strdup(game)) == NULL)
            return 84;
        print_some_lingo(size2);
        if (launch_game_loop(objective, copy) == 2) {
            my_putstr("You won!\n");
            return 0;
        }
        size2 = size2 + 1;
    }
    my_putstr("You lost!\n");
    return 0;
}
