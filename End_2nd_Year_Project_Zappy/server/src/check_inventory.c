/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** check_inventory.c
*/

#include "server.h"

void *check_inventory(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    map_t *map = content->map;
    queue_t *queue = content->client->queue;

    send_player_inventory_ai(client);
    return (NULL);
}
