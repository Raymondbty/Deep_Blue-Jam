/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_player_info2.c
*/

#include "server.h"

void send_connection_player_gui(client_t *client, int fd)
{
    dprintf(fd, "pnw %d %d %d %d %d %s\n", client->id, client->pos.x,
    client->pos.y, client->orientation, client->level, client->actual_team);
}

void send_pos_all_player(client_t *client, int fd)
{
    client_t *tmp_client = client;

    for (; tmp_client != NULL; tmp_client = tmp_client->next)
        if (tmp_client->fd != fd)
            send_player_pos_gui(tmp_client, fd);
}
