/*
** EPITECH PROJECT, 2023
** xopen.c
** File description:
** open a file or create a new file if it doesn't exist
*/
#include "nm.h"

int xopen(char *filename)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "nm: %s: File format not recognized\n", filename);
        return (-1);
    }
    return (fd);
}
