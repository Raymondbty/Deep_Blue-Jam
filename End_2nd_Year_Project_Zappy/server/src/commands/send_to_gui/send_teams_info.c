/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_teams_info.c
*/

#include "server.h"

void send_teams_info_gui(client_t *client, team_t **teams)
{
    for (int i = 0; teams[i] != NULL; ++i) {
        dprintf(client->fd, "tna %s\n", teams[i]->name);
    }
}
