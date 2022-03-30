/*
** EPITECH PROJECT, 2022
** solver.h
** File description:
** solver
*/

#ifndef _GENERATOR_H_
    #define _GENERATOR_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdbool.h>
    #include <time.h>
    #include <string.h>
typedef struct gen_s {
    int modulo;
    int up;
    int down;
    int x;
    int y;
    char **map;
} gen_t;
typedef struct emp_s {
    int a;
    int b;
} emp_t;

void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int main(int argc, char **argv);
int do_h(char **argv);
int check_args(int argc, char **argv);
int verify_if_number(char *argv);
void make_imperfect(gen_t *gen, emp_t *new);
int check_tiles_wall(gen_t *gen, emp_t *emp);
void line_selected(int a, gen_t *gen);
int verify_surrounding(gen_t *gen, emp_t *emp);
void perfect_verify_surrounding(int y, gen_t *gen);
void load_line_1(char *line, int x);
void load_all_lines(char *line, int x);
char **load_maze(int x, int y, gen_t *gen);
void perfect_check_tiles_wall(int a, int b, gen_t *gen);
void generate_imperfect_map(gen_t *gen);
void clear_path(char *line, int x);
char **generate_perfect_map(char **argv, gen_t *gen);
void print_map(gen_t *gen);
int line_size(gen_t *gen);
void clear_path_perfect(char *line, int x);
char **make_perfect(int x, int y, gen_t *gen);
void free_maze(gen_t *gen);
int set_maze(gen_t *gen);
void move_forward(gen_t *gen, emp_t *emp);
int set_road(gen_t *gen, emp_t *emp);
int support_main(int argc, char **argv, gen_t *gen);
#endif
