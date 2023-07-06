/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_player_info.c
*/

#include "server.h"

void send_player_pos_gui(client_t *client, int fd)
{
    dprintf(fd, "ppo %d %d %d %d\n", client->id, client->pos.x,
    client->pos.y, client->orientation);
}

void send_player_level_gui(client_t *client, int fd)
{
    dprintf(fd, "plv %d %d\n", client->id, client->level);
}

void send_player_inventory_gui(client_t *client, int fd)
{
    dprintf(fd, "pin %d %d %d %d %d %d %d %d %d %d\n", client->id,
    client->pos.x, client->pos.y, client->ressources.nbr_food,
    client->ressources.nbr_linemate, client->ressources.nbr_deraumere,
    client->ressources.nbr_sibur, client->ressources.nbr_mendiane,
    client->ressources.nbr_phiras, client->ressources.nbr_thystame);
}

void send_incantation_gui(client_t **clients, int fd)
{
    client_t **tmp_client = clients;

    dprintf(fd, "pic %d %d %d", tmp_client[0]->pos.x, tmp_client[0]->pos.y,
    tmp_client[0]->level);
    for (; *tmp_client != NULL; tmp_client++)
        dprintf(fd, " %d", (*tmp_client)->id);
    dprintf(fd, "\n");
}

void send_incantation_result_gui(client_t *client, int fd, int result)
{
    dprintf(fd, "pie %d %d %d\n", client->pos.x, client->pos.y, result);
}
