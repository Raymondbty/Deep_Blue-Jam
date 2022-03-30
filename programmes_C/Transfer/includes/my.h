/*
** EPITECH PROJECT, 2019
** 107transfer
** File description:
** my.h
*/
#ifndef	MY_H_
    #define MY_H_
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <stddef.h>
    #include <math.h>

typedef	struct transfer_s
{
    int a;
    double b;
    double c;
    double d;
    int w;
    int s;
    int p;
    double e;
    double f;
    double g;
} transfer_t;
void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
int main(int argc, char **argv);
int error_handling(char *param);
char **double_array(char *str, char c, int i, int j);
void do_h(void);
double do_transfer(int argc, char *argv, double A);
char back_value(char z);
void reload(transfer_t *transfer);
#endif
