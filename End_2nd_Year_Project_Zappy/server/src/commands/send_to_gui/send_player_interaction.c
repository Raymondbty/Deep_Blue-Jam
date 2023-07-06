/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_player_interaction.c
*/

#include "server.h"

void send_player_egg_laying_gui(client_t *client, int fd)
{
    dprintf(fd, "pfk %d\n", client->id);
}

void send_player_drop_ressources_gui(client_t *client, int fd,
int nbr_ressources)
{
    dprintf(fd, "pdr %d %d\n", client->id, nbr_ressources);
}

void send_player_cllect_ressources_gui(client_t *client, int fd,
int nbr_ressources)
{
    dprintf(fd, "pgt %d %d\n", client->id, nbr_ressources);
}

void send_player_death_gui(client_t *client, int fd)
{
    dprintf(fd, "pdi %d\n", client->id);
}
