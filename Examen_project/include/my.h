/*
** EPITECH PROJECT, 2022
** my.h
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <string.h>
    #include <time.h>
    #include <stddef.h>
    #include <stdio.h>

//MAIN
int help_main(int argc, char **argv, char *objective, char *game);
int main(int argc, char **argv);
//GAME LOOP
int help_initialize_lingo(char *objective, char *game);
int initialize_lingo(char *objective, char *game, size_t size, char *copy);
char *display_clues(char *attempt, char *objective, char *game);
char *error_handling_take_input(char *objective);
int place_clue_almost_right(char *objective, char chara, char *game);
int launch_game_loop(char *word, char *game);
void print_start(void);
int print_some_lingo(size_t size2);
//ERROR HANDLING
char *error_handling_take_input(char *objective);
int verify_arg(int argc);
//GETFILE & MALLOC
char **malloc_content(char **content, char **array, size_t size, char **nope);
char **help_malloc_content(char **content);
char *help_take_file(char *path);
char *take_file(char *path, size_t a, size_t b, char **content);
//FREE
char *free_random(char **content);
int loop_free(char *loop);
//CLEAN STRING/**CHAR
void mr_clean_tab_bis(char **content);
void mr_clean_tab(char **content);
void mr_clean_string(char *string);
//LIB
void my_putchar(char c);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_read(int nb, int n);
int my_put_nbr(int nb);
#endif
