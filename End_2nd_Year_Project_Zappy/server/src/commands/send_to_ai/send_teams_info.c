/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_teams_info.c
*/

#include "server.h"

void *send_nbr_unused_slot_team(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    team_t **list_teams = content->teams;
    team_t *team = get_team(client->actual_team, list_teams);

    dprintf(client->fd, "%d\n", team->nb_unused_slots);
}
