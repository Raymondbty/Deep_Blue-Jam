/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** header file that contains the prototypes of all the function in libmy.a
*/

#ifndef N4S_H_
    #define N4S_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #define END "STOP_SIMULATION\n"
    #define FINISH "Track Cleared"
    #define READ_SIZE 1

char *get_next_line(const int fd);
char *add(char *line, int deal, char *buf, int *begin);
char *my_strncpy(char *dest, char *src, int n);
typedef struct n4s_s
{
    size_t size;
    char **infos;
    float *input;
    int roll;
}n4s_t;

typedef struct counter_s {
    int i;
    int j;
    int k;
} counter_t;

///src fonction
char *get_next_line(const int fd);
int simulation_finished(char *infos);
int stop_simulation(n4s_t *n4s);
int wall_on_left(n4s_t *n4s);
int wall_on_right(n4s_t *n4s);
int road_clear_or_end(n4s_t *n4s);
int make_rays(n4s_t *n4s);
char *string_free(char *str);
int roll_back(n4s_t *n4s);
int call_turn(n4s_t *n4s);
int turn_right(n4s_t *n4s);
int turn_left(n4s_t *n4s);
int detect_environment(n4s_t *n4s);
char **str_to_word_array(char *str, char delim);
int do_parse(n4s_t *n4s);
void roll_back_left(n4s_t *n4s);
int my_strcmp(char const *s1, char const *s2);

//lib futctions
void my_putchar(char c);
int my_putstr(char *str);
int my_isneg(int n);
char *my_revstr(char *str);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_find_prime_sup(int nb);
int my_getnbr(char const *str);
int my_is_prime(int nb);
int my_put_nbr(int nb);
int my_showmem(char const *str, int size);
int my_showstr(char const *str);
void my_sort_int_array(int *array, int size);
char *my_strcapitalize(char *str);
int my_strcmp(char const *s1, char const *s2);
int my_str_isalpha(char const *str);
int my_str_islower(char const *str);
int my_str_isnum(char const *str);
int my_str_isprintable(char const *str);
int my_str_isupper(char const *str);
int my_strlen(char const *str);
char *my_strlowcase(char *str);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strstr(char *str, char const *to_find);
char *my_strupcase(char *str);
void my_swap(int *a, int *b);
int print_the_nbr(int number);
char *my_strdup(char const *src);
char *my_memset(char *str, int i, char fill);
int convert_base(int number, int base);
int my_revnbr(int nbr, int is_zero_to_add_base_2);
int my_arraylen(char const **array);
void my_putcharerror(char c);
int my_putstrerror(char *str);
#endif
