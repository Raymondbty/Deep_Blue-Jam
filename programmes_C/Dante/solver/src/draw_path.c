/*
** EPITECH PROJECT, 2022
** Dante
** File description:
** draw the path on the char ** maze
*/
#include <unistd.h>
#include "solver.h"

static const path_checker_fun_t TAB[] = {
    { 0, &checker_x_0 },
    { 1, &checker_x_0 },
    { 2, &checker_x_0 },
    { 3, &checker_x_max },
    { 4, &checker_x_max },
    { 5, &checker_x_max },
    { 6, &checker_x_norm },
    { 7, &checker_x_norm },
};

int is_limit_maze(vector2i_t *pos, vector2i_t *size_maze)
{
    if (pos->x == 0 && pos->y == 0)
        return (0);
    if (pos->x == 0 && pos->y == size_maze->y)
        return (1);
    if (pos->x == 0 && (pos->y > 0 && pos->y < size_maze->y))
        return (2);
    if (pos->x == size_maze->x && pos->y == 0)
        return (3);
    if (pos->x == size_maze->x && pos->y == size_maze->y)
        return (4);
    if (pos->x == size_maze->x && (pos->y > 0 && pos->y < size_maze->y))
        return (5);
    if ((pos->x > 0 && pos->x < size_maze->x) && pos->y == 0)
        return (6);
    if ((pos->x > 0 && pos->x < size_maze->x) && pos->y == size_maze->y)
        return (7);
    return (42);    
}

void call_checher_next_pos(int **int_maze, char **maze, vector2i_t *pos,
                        vector2i_t *size_maze)
{
    int to_call = is_limit_maze(pos, size_maze);

    for (int i = 0; i < 8; ++i) {
        if (to_call == TAB[i].cond) {
            TAB[i].fun_ptr(to_call, int_maze, maze, pos);
            return;
        }
    }
}

void draw_path(int **int_maze, char **maze, vector2i_t *size_maze)
{
    vector2i_t pos = { 0 };

    maze[0][0] = 'o';
    while (maze[size_maze->y][size_maze->x] == '*') {
        if (is_limit_maze(&pos, size_maze) == 42) {
            call_check_pos(int_maze, maze, &pos, &(counter_t){ 0, 1, 4 });
        } else {
            call_checher_next_pos(int_maze, maze, &pos, size_maze);
        }
    }
}
