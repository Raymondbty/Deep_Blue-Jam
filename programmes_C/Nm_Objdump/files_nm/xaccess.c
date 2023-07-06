/*
** EPITECH PROJECT, 2023
** xaccess.c
** File description:
** check whether a process has permission to access a file or directory
*/
#include "nm.h"

int xaccess(char *filename)
{
    if (access(filename, F_OK) == -1) {
        fprintf(stderr, "nm: '%s': No such file\n", filename);
        return (-1);
    }
    return (0);
}
