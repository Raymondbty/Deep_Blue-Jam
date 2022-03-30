/*
** EPITECH PROJECT, 2020
** dante
** File description:
** maze generator main file
*/
#include "../include/generator.h"

int check_args(int argc, char **argv)
{
    int a = 0;

    for (a = 1; a < argc; a = a + 1) {
        if (verify_if_number(argv[a]) == a && a < 3) {
            return 84;
        }
        if (a == 3 && argv[3][0] == 'p' && argv[3][7] == '\0') {
            return 84;
        }
    }
    return 0;
}

int verify_if_number(char *argv)
{
    int a = 0;

    for (a = 0; argv[a] != '\0'; a = a + 1) {
        if (argv[a] < '0' || argv[a] > '9') {
            return 84;
        }
    }
    return 0;
}
