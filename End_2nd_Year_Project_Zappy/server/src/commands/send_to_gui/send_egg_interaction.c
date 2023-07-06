/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_egg_interaction.c
*/

#include "server.h"

void send_egg_laying_by_player_gui(egg_t *egg, int fd)
{
    dprintf(fd, "enw %d %d %d %d\n", egg->id, egg->id_parent, egg->pos.x,
    egg->pos.y);
}

void send_player_connect_to_egg_gui(egg_t *egg, int fd)
{
    dprintf(fd, "ebo %d\n", egg->id);
}

void send_egg_death_gui(egg_t *egg, int fd)
{
    dprintf(fd, "edi %d\n", egg->id);
}

void send_all_eggs_gui(egg_t *egg, int fd)
{
    egg_t *tmp = egg;

    for (; tmp != NULL; tmp = tmp->next)
        send_egg_laying_by_player_gui(tmp, fd);
}
