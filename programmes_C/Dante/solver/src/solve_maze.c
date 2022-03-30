/*
** EPITECH PROJECT, 2022
** solve_map.c
** File description:
** solve map
*/
#include <unistd.h>
#include "solver.h"
#include "my.h"

void check_pos(int *distance, int **int_maze, counter_t *i_j,
            vector2i_t *size_maze)
{
    if (int_maze[i_j->i][i_j->j] == 0) {
        if ((i_j->i + 1 <= size_maze->y &&
            int_maze[i_j->i + 1][i_j->j] > 0) ||
            (i_j->i - 1 >= 0 &&
            int_maze[i_j->i - 1][i_j->j] > 0) ||
            (i_j->j + 1 <= size_maze->x &&
            int_maze[i_j->i][i_j->j + 1] > 0) ||
            (i_j->j - 1 >= 0 &&
            int_maze[i_j->i][i_j->j - 1] > 0)) {
            int_maze[i_j->i][i_j->j] = *distance + 1;
            ++(*distance);
        }
    }
}

void browse_maze(int *distance, int **int_maze, vector2i_t *size_maze)
{
    counter_t i_j = { .i = size_maze->y, .j = size_maze->x, .k = 0 };

    while (i_j.i >= 0) {
        while (i_j.j >= 0) {
            check_pos(distance, int_maze, &i_j, size_maze);
            --i_j.j;
        }
        i_j.j = size_maze->x - 1;
        --i_j.i;
    }
}

int solve_map(int **int_maze, char **maze)
{
    int distance = 1;
    int len_tab = my_arraylen((const char **)maze);
    int len_line = my_strlen((const char *)maze[0]);
    vector2i_t size_maze = { .x = len_line - 1, .y = len_tab - 1 };

    if (int_maze[len_tab - 1][len_line - 1] == -1 || int_maze[0][0] == -1) {
        my_putstr("no solution found\n");
        return (0);
    }
    int_maze[len_tab - 1][len_line - 1] = 1;
    while (int_maze[0][0] == 0) {
        browse_maze(&distance, int_maze, &size_maze);
    }
    draw_path(int_maze, maze, &size_maze);
    for (int i = 0; i < len_tab - 1; ++i) {
        my_putstr(maze[i]);
        my_putchar('\n');
    }
    my_putstr(maze[len_tab - 1]);
    return 0;
}
