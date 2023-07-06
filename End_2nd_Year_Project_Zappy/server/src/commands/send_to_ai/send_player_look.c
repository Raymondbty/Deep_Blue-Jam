/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_player_look.c
*/

#include "server.h"

void print_nbr_info(client_t *client, char *info, int nbr_time)
{
    for (int i = 0; i < nbr_time; ++i) {
        dprintf(client->fd, " %s", info);
    }
}

void print_all_info(client_t *client, tile_t *tiles, int i)
{
    if (i == 0)
        print_nbr_info(client, "player", tiles->nbr_player - 1);
    else
        print_nbr_info(client, "player", tiles->nbr_player);
    print_nbr_info(client, "food", tiles->ressources->nbr_food);
    print_nbr_info(client, "linemate", tiles->ressources->nbr_linemate);
    print_nbr_info(client, "deraumere",
    tiles->ressources->nbr_deraumere);
    print_nbr_info(client, "sibur", tiles->ressources->nbr_sibur);
    print_nbr_info(client, "mendiane", tiles->ressources->nbr_mendiane);
    print_nbr_info(client, "phiras", tiles->ressources->nbr_phiras);
    print_nbr_info(client, "thystame", tiles->ressources->nbr_thystame);
}

void *send_look_around_ai(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    tile_t **tiles = look(client, content->map);
    queue_t *queue = content->queue;

    write(client->fd, "[ player", 8);
    for (int i = 0; tiles[i] != NULL; ++i) {
        if (i != 0) {
            write(client->fd, ",", 1);
        }
        print_all_info(client, tiles[i], i);
    }
    write(client->fd, " ]\n", 3);
    free(tiles);
    return (NULL);
}
