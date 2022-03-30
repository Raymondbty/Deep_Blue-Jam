/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** my.h
*/
#ifndef MY_H_
    #define MY_H_
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdarg.h>
    #include <string.h>
    #include <ncurses.h>
typedef struct soko_s
{
    int sz_map;
    char *buffer;
    char *buffer2;
    int p_position2;
    int p_position;
    int line;
    int cols;
    int *pos_O;
} soko_t;

void my_putchar(char c);
int my_put_nbr(int nb);
int my_strlen(char const *str);
int my_putstr(char const *str);
int main(int argc, char **argv);

void do_win(void);

int win_condition(soko_t *sokoban);
void verify_emacs_terminal(soko_t *sokoban);
int verify_1_player(soko_t *sokoban);
int open_file(soko_t *sokoban, char *argv);
int error_report(soko_t *sokoban);
void check_nb_of_x(soko_t *sokoban);
void check_nb_col_l(soko_t *sokoban);
int storage_boxes(soko_t *sokoban);
int check_char(soko_t *sokoban);
int error_trap_square(soko_t *sokoban);

void change_o_for_x(soko_t *sokoban);
int handle_keyboard(soko_t *sokoban);
int launch_soko(soko_t *sokoban);
void help_count_lc(soko_t *sokoban);
void respawn(soko_t *sokoban);
void reload_map(soko_t *sokoban);
void do_h(void);

void down_wall_handling(int pos_p, soko_t *sokoban);
int react_down(soko_t *sokoban);
void move_down(int pos_p, soko_t *sokoban);

void left_wall_handling(int pos_p, soko_t *sokoban);
int react_left(soko_t *sokoban);
void move_left(int pos_p, soko_t *sokoban);

void right_wall_handling(int pos_p, soko_t *sokoban);
int react_right(soko_t *sokoban);
void move_right(int pos, soko_t *sokoban);

void up_wall_handling(int p_pos, soko_t *sokoban);
void move_up(int p_pos, soko_t *sokoban);
int react_up(soko_t *sokoban);
#endif
