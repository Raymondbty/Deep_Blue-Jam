/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_movement.c
*/

#include "server.h"

void send_player_inventory_ai(client_t *client)
{
    dprintf(client->fd, "[ food %d, linemate %d, deraumere %d, sibur %d,",
    client->ressources.nbr_food, client->ressources.nbr_linemate,
    client->ressources.nbr_deraumere, client->ressources.nbr_sibur);
    dprintf(client->fd, " mendiane %d, phiras %d, thystame %d ]\n",
    client->ressources.nbr_mendiane, client->ressources.nbr_phiras,
    client->ressources.nbr_thystame);
}

void send_player_death_ai(client_t *client)
{
    dprintf(client->fd, "dead\n");
}

void send_player_incantation_ai(client_t *client)
{
    dprintf(client->fd, "Elevation underway\n");
    dprintf(client->fd, "Current level: %d\n", client->level);
}
