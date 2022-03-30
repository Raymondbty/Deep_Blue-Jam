/*
** EPITECH PROJECT, 2022
** dante
** File description:
** create the maze char **
*/
#include <stdlib.h>
#include "my.h"

int line_lenght(const char *str)
{
    int i = 0;

    while (str[i] != '\n') {
        ++i;
    }
    return (i);
}

int count_occurence_char(const char *str, char to_count)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (str[i] == to_count) {
            ++count;
        }
        ++i;
    }
    return (count);
}

char **create_tab_maze(char *map)
{
    int i = 0;
    int len_tab = count_occurence_char((const char *)map, '\n');
    int len_line = line_lenght((const char *) map);
    char **maze = malloc(sizeof(char *) * (size_t)(len_tab + 1));

    if (maze == NULL)
        return (NULL);
    while (i < len_tab) {
        maze[i] = malloc(sizeof(char) * (size_t)(len_line + 1));
        if (maze[i] == NULL)
            return (NULL);
        maze[i][0] = '\0';
        my_strncat(maze[i], &map[(len_line + 1) * i], len_line);
        ++i;
    }
    maze[i] = NULL;
    return (maze);
}

void fill_int_maze(int i, int j, int **int_maze, char **maze)
{
    if (maze[i][j] == '*') {
        int_maze[i][j] = 0;
    } else {
        int_maze[i][j] = -1;
    }
}

int **create_int_maze(char **maze)
{
    int i = 0;
    int j = 0;
    int len_tab = my_arraylen((const char **)maze);
    int len_line = my_strlen(maze[0]);
    int **int_maze = malloc(sizeof(int *) * len_tab);

    if (int_maze == NULL)
        return (NULL);
    while (i < len_tab) {
        int_maze[i] = malloc(sizeof(int) * len_line);
        if (int_maze[i] == NULL)
            return (NULL);
        while (j < len_line) {
            fill_int_maze(i, j, int_maze, maze);
            ++j;
        }
        j = 0;
        ++i;
    }
    return (int_maze);
}
