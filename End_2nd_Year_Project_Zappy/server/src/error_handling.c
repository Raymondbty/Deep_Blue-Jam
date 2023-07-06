/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** error_handling.c
*/

#include "error_handling.h"

void help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height\
    -n name1 name2 ... -c clientsNb -f freq\n\
    \tport\t\tis the port number\n\
    \twidth\t\tis the width of the world\n\
    \theight\t\tis the height of the world\n\
    \tnameX\t\tis the name of the team X\n\
    \tclientsNb\tis the number of authorized clients per team\n\
    \tfreq\t\tis the reciprocal of time unit for execution of actions\n");
}

int check_arg(char *arg, char *flag_arg)
{
    for (int i = 0; arg[i] != '\0'; ++i)
        if (!isdigit(arg[i])) {
            printf("Error: argument '%s' need to be an int not negative\n",
            flag_arg);
            return 84;
        }
    if (atoi(arg) < 0) {
        printf("Error: argument '%s' need to be a positive number\n",
        flag_arg);
        return 84;
    }
    return 0;
}

int check_flag(char *flag)
{
    char *flags[5] = {"-p", "-x", "-y", "-c", NULL};

    for (int i = 0; flags[i] != NULL; ++i) {
        if (strcmp(flag, flags[i]) == 0) {
            return 0;
        }
    }
    return 84;
}

int check_flag_f(char *flag)
{
    if (strpbrk(flag, ".") == 0) {
        if (!isdigit(flag[0])) {
            printf("Error: argument '%s' need to be an float not negative\n",
            flag);
            return 84;
        }
    }
    if (atof(flag) < 0) {
        printf("Error: argument '%s' need to be a positive number\n",
        flag);
        return 84;
    }
    return 0;
}

int error_handling(int argc, char **argv)
{
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 ||
    strcmp(argv[1], "-help") == 0)) {
        help();
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < argc - 1; ++i) {
        if (check_flag(argv[i]) == 0 &&
        check_arg(argv[i + 1], argv[i]) == 84)
            return 84;
        if (strcmp(argv[i], "-f") == 0 && check_flag_f(argv[i + 1]) == 84)
            return 84;
    }
    if (check_flag(argv[argc - 1]) == 0) {
        printf("Error: argument '%s' need a value\n", argv[argc - 1]);
        return 84;
    }
    return 0;
}
