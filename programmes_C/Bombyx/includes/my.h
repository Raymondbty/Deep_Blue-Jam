/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** my.h
*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef _MY_H_
    #define _MY_H

void do_h(void);
void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
int main(int argc, char **argv);
int exo3arg(char **argv);
int exo4arg(char **argv);
int error_handling(int argc, char **argv);
#endif
