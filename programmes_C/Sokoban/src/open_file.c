/*
** EPITECH PROJECT, 2022
** open_file.c
** File description:
** open_file
*/
#include "../include/my.h"

int open_file(soko_t *sokoban, char *argv)
{
    int size = 50000;
    int fd = open(argv, O_RDONLY);

    sokoban->buffer = malloc(sizeof(char) * size);
    if (fd == -1) {
        return 84;
    }
    read(fd, sokoban->buffer, size - 1);
    return 0;
}
