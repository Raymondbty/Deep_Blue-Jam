/*
** EPITECH PROJECT, 2022
** Dante
** File description:
** simpe condition to check next pos
*/
#include "solver.h"

static const check_fun_t TAB_FUN[] = {
    { &check_next_x },
    { &check_prev_x },
    { &check_next_y },
    { &check_prev_y }
};

int check_next_x(int **int_maze, char **maze, vector2i_t *pos)
{
    if (int_maze[pos->y][pos->x + 1] < int_maze[pos->y][pos->x] &&
        int_maze[pos->y][pos->x + 1] > 0) {
        ++pos->x;
        maze[pos->y][pos->x] = 'o';
        return (0);
    }
    return (1);
}

int check_prev_x(int **int_maze, char **maze, vector2i_t *pos)
{
    if (int_maze[pos->y][pos->x - 1] < int_maze[pos->y][pos->x] &&
        int_maze[pos->y][pos->x - 1] > 0) {
        --pos->x;
        maze[pos->y][pos->x] = 'o';
        return (0);
    }
    return (1);
}

int check_next_y(int **int_maze, char **maze, vector2i_t *pos)
{
    if (int_maze[pos->y + 1][pos->x] < int_maze[pos->y][pos->x] &&
        int_maze[pos->y + 1][pos->x] > 0) {
        ++pos->y;
        maze[pos->y][pos->x] = 'o';
        return (0);
    }
    return (1);
}

int check_prev_y(int **int_maze, char **maze, vector2i_t *pos)
{
    if (int_maze[pos->y - 1][pos->x] < int_maze[pos->y][pos->x] &&
        int_maze[pos->y - 1][pos->x] > 0) {
        --pos->y;
        maze[pos->y][pos->x] = 'o';
        return (0);
    }
    return (1);
}

int call_check_pos(int **int_maze, char **maze, vector2i_t *pos,
                counter_t *counter_while)
{
    while (counter_while->i < counter_while->k) {
        if (TAB_FUN[counter_while->i].fun_ptr(int_maze, maze, pos) == 0) {
            return (0);
        }
        counter_while->i += counter_while->j;
    }
    return (1);
}
