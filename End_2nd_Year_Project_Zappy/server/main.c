/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** main.c
*/

#include "error_handling.h"
#include "server.h"

int main(int argc, char **argv)
{
    if (error_handling(argc, argv) == 84)
        return (84);
    return server_main(argv);
}
