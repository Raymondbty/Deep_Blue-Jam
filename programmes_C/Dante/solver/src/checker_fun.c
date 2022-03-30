/*
** EPITECH PROJECT, 2022
** Dante
** File description:
** checker path fun
*/
#include "solver.h"

void checker_x_0(int option, int **int_maze, char **maze, vector2i_t *pos)
{
    if (option == 0) {
        call_check_pos(int_maze, maze, pos, &(counter_t){ 0, 2, 3 });
    } else if (option == 1) {
        call_check_pos(int_maze, maze, pos, &(counter_t){ 0, 3, 4 });
    } else {
        if (call_check_pos(int_maze, maze, pos, &(counter_t){ 2, 1, 4}) == 1)
            return;
        else
            check_next_x(int_maze, maze, pos);
    }
}

void checker_x_max(int option, int **int_maze, char **maze, vector2i_t *pos)
{
    if (option == 3) {
        call_check_pos(int_maze, maze, pos, &(counter_t){ 1, 1, 3 });
    } else if (option == 4) {
        call_check_pos(int_maze, maze, pos, &(counter_t){ 1, 2, 4 });
    } else {
        call_check_pos(int_maze, maze, pos, &(counter_t){ 1, 1, 4 });
    }
}

void checker_x_norm(int option, int **int_maze, char **maze, vector2i_t *pos)
{
    if (option == 6) {
        call_check_pos(int_maze, maze, pos, &(counter_t){ 0, 1, 3 });
    } else if (option == 7) {
        if (call_check_pos(int_maze, maze, pos, &(counter_t){ 0, 1, 2 }) == 0)
            return;
        else
            check_prev_y(int_maze, maze, pos);
    }
}
