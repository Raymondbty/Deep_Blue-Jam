/*
** EPITECH PROJECT, 2022
** put_nbr
** File description:
** put_nbr
*/
#include "my.h"

int my_read(int nb, int n)
{
    int x = nb / 10;
    int y = nb % 10;

    if (n && !x) {
        my_putchar('-');
    } if (x) {
        my_read(x, n);
    } if (n) {
        my_putchar('0' + -y);
    } else {
        my_putchar('0' + y);
    }
    return (0);
}

int my_put_nbr(int nb)
{
    int n = nb < 0;
    my_read(nb, n);
    return (0);
}
