/*
** EPITECH PROJECT, 2022
** solver.h
** File description:
** solver
*/

#ifndef _SOLVER_H_
    #define _SOLVER_H_

typedef struct counter {
    int i;
    int j;
    int k;
} counter_t;

typedef struct vector2i {
    int x;
    int y;
} vector2i_t;

typedef struct path_checker_fun {
    int cond;
    void (*fun_ptr) (int, int **, char **, vector2i_t *);
} path_checker_fun_t;

typedef struct check_fun {
    int (*fun_ptr) (int **, char **, vector2i_t *);
} check_fun_t;

int main(int argc, char **argv);

char *open_file(char *argv);

char **create_tab_maze(char *map);
int count_occurence_char(const char *str, char to_count);
int line_lenght(const char *str);
int **create_int_maze(char **maze);
void fill_int_maze(int i, int j, int **int_maze, char **maze);

int solve_map(int **int_maze, char **maze);
int is_limit_maze(vector2i_t *pos, vector2i_t *size_maze);
void draw_path(int **int_maze, char **maze, vector2i_t *size_maze);
void call_checher_next_pos(int **int_maze, char **maze, vector2i_t *pos,
                        vector2i_t *size_maze);
void checker_x_0(int option, int **int_maze, char **maze, vector2i_t *pos);
void checker_x_max(int option, int **int_maze, char **maze, vector2i_t *pos);
void checker_x_norm(int option, int **int_maze, char **maze, vector2i_t *pos);
int call_check_pos(int **int_maze, char **maze, vector2i_t *pos,
                    counter_t *counter_while);
int check_prev_y(int **int_maze, char **maze, vector2i_t *pos);
int check_next_y(int **int_maze, char **maze, vector2i_t *pos);
int check_prev_x(int **int_maze, char **maze, vector2i_t *pos);
int check_next_x(int **int_maze, char **maze, vector2i_t *pos);


#endif
