/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** main
*/
#include "../includes/my.h"

int number_counter(char const *str, int type)
{
    int i = 0;
    int num = 0;
    int comma_check = 0;

    while (str[i] != '\0') {
        if (type == 0) {
            if ((str[i] >= '0' && str[i] <= '9') || str[i] == '\0') {
                num++;
            } else {
                return (-1);
            }
              i++;
        }
        if (type == 1) {
            if (str[0] == '.')
                return -1;
            if (comma_check > 1)
                return -1;
            if (str[i] == '.' && str[i + 1] != '\0') {
                comma_check ++;
            } else if ((str[i] >= '0' && str[i] <= '9') || str[i] == '\0') {
                num++;
            } else {
                return (-1);
            }
              i++;
        }
    }
    return 0;
}

int check_all_args(int ac, char **av, int type)
{
    int i = 1;

    while (i < ac) {
        if (ac == 3 && i == 2) {
            if (number_counter(av[i], 1) == -1)
                return 84;
            i++;
        } else {
            if (number_counter(av[i], 0) == -1)
                return 84;
            i++;
        }
    }
    return 0;
}

int error_handling(int argc, char **argv)
{
    if (argc == 3) {
        if (check_all_args(argc, argv, 0) != 84) {
            exo3arg(argv);
        } else {
            return 84;
        }
    } else if (argc == 4) {
        if (check_all_args(argc, argv, 1) != 84) {
            exo4arg(argv);
        } else {
            return 84;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        if (argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0') {
            do_h();
        } else {
            printf("not enought arguments, 3 or 4 required\n");
            return 84;
        }
    } else if (argc == 3 || argc == 4) {
        if (error_handling(argc, argv) == 84) {
            return 84;
        } else {
            error_handling(argc, argv);
        }
    } else {
        printf("error : uncorrect nb of arguments, 3 or 4 required\n");
        return 84;
    }
}
