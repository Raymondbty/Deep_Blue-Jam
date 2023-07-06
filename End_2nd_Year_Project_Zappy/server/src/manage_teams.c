/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** manage_teams.c
*/

#include "server.h"

team_t **create_teams(char **argv, team_t **teams, int max_clients)
{
    int nbr = 1;

    for (int i = 0; argv[i] != NULL; ++i)
        for (; strcmp(argv[i], "-n") == 0 && argv[i + nbr] != NULL &&
        argv[i + nbr][0] != '-'; ++nbr) {
            teams[nbr - 1] = malloc(sizeof(team_t));
            teams[nbr - 1]->name = strdup(argv[i + nbr]);
            teams[nbr - 1]->clients = malloc(sizeof(client_t *) *
            (max_clients + 1));
            teams[nbr - 1]->nb_unused_slots = max_clients;
            teams[nbr - 1]->nb_clients = 0;
            teams[nbr - 1]->max_clients = max_clients;
            teams[nbr - 1]->nbr_eggs = 0;
        }
    teams[nbr] = NULL;
    return teams;
}

team_t *get_team(char *name, team_t **teams)
{
    team_t **tmp = teams;

    for (; *tmp != NULL; ++tmp) {
        if (strcmp((*tmp)->name, name) == 0)
            return &(*tmp)[0];
    }
    return NULL;
}

void destroy_all_teams(team_t **teams)
{
    team_t **tmp = teams;

    for (; *tmp != NULL; ++tmp) {
        free((*tmp)->name);
        free((*tmp)->clients);
        free(*tmp);
    }
    free(teams);
}
