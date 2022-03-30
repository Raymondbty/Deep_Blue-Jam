/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "solver.h"

int verify_map(char *buffer)
{
    int i = 0;

    while (buffer[i] != '\0') {
        if (buffer[i] == 'X' || buffer[i] == '*') {
            ++i;
        } else {
            return (-1);
        }
    }
    return 0;
}

char *open_file(char *file)
{
    int fd = open(file, O_RDONLY);
    struct stat buf;
    char *buffer = NULL;

    if (fd == -1 || stat(file, &buf) == -1)
        return (NULL);
    buffer = malloc(sizeof(char) * (size_t)(buf.st_size + 1));
    if (buffer == NULL)
        return (NULL);
    if (read(fd, buffer, buf.st_size) == -1)
        return (NULL);
    buffer[buf.st_size] = '\0';
    if (verify_map(buffer) == -1)
        return (NULL);
    return (buffer);
}

int main(int argc, char **argv)
{
    char *map = NULL;
    char **maze = NULL;
    int **int_maze = NULL;

    if (argc != 2)
        return 84;
    if ((map = open_file(argv[1])) == NULL)
        return 84;
    else {
        maze = create_tab_maze(map);
        int_maze = create_int_maze(maze);
        if (maze == NULL || int_maze == NULL)
            return (84);
        solve_map(int_maze, maze);
    }
    return 0;
}
