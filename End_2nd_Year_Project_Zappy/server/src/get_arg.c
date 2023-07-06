/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** get_arg.c
*/

#include "server.h"

int get_flag (char **argv, char *flag)
{
    int nbr = -1;

    for (int i = 0; argv[i] != NULL; ++i) {
        if (strcmp(argv[i], flag) == 0 && argv[i + 1] != NULL && strcmp(flag,
        "-f") == 0)
            return atof(argv[i + 1]) * 1000;
        if (strcmp(argv[i], flag) == 0 && argv[i + 1] != NULL)
            return atoi(argv[i + 1]);
    }
    return nbr;
}

team_t **get_teams_names(char **argv, int max_clients)
{
    team_t **teams = NULL;
    int nbr = 1;

    if (max_clients <= 0) {
        printf("Error: max clients must be positive\n");
        return NULL;
    }
    for (int i = 0; argv[i] != NULL; ++i)
        for (; strcmp(argv[i], "-n") == 0 && argv[i + nbr] != NULL &&
        argv[i + nbr][0] != '-'; ++nbr);
    teams = malloc(sizeof(team_t *) * (nbr + 1));
    teams = create_teams(argv, teams, max_clients);
    teams[nbr - 1] = NULL;
    return teams;
}
