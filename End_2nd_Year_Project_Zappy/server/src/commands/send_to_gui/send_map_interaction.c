/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_map_interaction.c
*/

#include "server.h"

void send_expulse_gui(client_t *client, int fd)
{
    dprintf(fd, "pex %d\n", client->id);
}

void send_broadcast_gui(client_t *client, int fd, char *msg)
{
    dprintf(fd, "pbc %d %s\n", client->id, msg);
}
