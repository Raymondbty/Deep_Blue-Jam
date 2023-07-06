/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** client_movement.c
*/

#include "server.h"

void move_forward_v2(client_t *client, map_t *map)
{
    switch (client->orientation) {
        case SOUTH:
            map->tiles[client->pos.y][client->pos.x]->nbr_player--;
            client->pos.y = (client->pos.y + 1 > map->height - 1) ? 0 :
            client->pos.y + 1;
            map->tiles[client->pos.y][client->pos.x]->nbr_player++;
            break;
        case WEST:
            map->tiles[client->pos.y][client->pos.x]->nbr_player--;
            client->pos.x = (client->pos.x - 1 < 0) ? map->width - 1 :
            client->pos.x - 1;
            map->tiles[client->pos.y][client->pos.x]->nbr_player++;
            break;
    }
}

void move_forward_v1(client_t *client, map_t *map)
{
    switch (client->orientation) {
        case NORTH:
            map->tiles[client->pos.y][client->pos.x]->nbr_player--;
            client->pos.y = (client->pos.y - 1 < 0) ? map->height - 1 :
            client->pos.y - 1;
            map->tiles[client->pos.y][client->pos.x]->nbr_player++;
            break;
        case EAST:
            map->tiles[client->pos.y][client->pos.x]->nbr_player--;
            client->pos.x = (client->pos.x + 1 > map->width - 1) ? 0 :
            client->pos.x + 1;
            map->tiles[client->pos.y][client->pos.x]->nbr_player++;
            break;
        default:
            move_forward_v2(client, map);
            break;
    }
}

void *move_forward(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    map_t *map = content->map;
    queue_t *queue = content->queue;
    client_t *gui = content->gui;

    move_forward_v1(client, map);
    send_ok_ai(client->fd);
    if (gui != NULL)
        send_player_pos_gui(client, gui->fd);
    return NULL;
}

void *turn_right(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    queue_t *queue = content->queue;
    client_t *gui = content->gui;

    client->orientation = (client->orientation + 1 > WEST) ? NORTH :
    client->orientation + 1;
    send_ok_ai(client->fd);
    if (gui != NULL)
        send_player_pos_gui(client, gui->fd);
    return NULL;
}

void *turn_left(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    queue_t *queue = content->queue;
    client_t *gui = content->gui;

    client->orientation = (client->orientation - 1 < NORTH) ? WEST :
    client->orientation - 1;
    send_ok_ai(client->fd);
    if (gui != NULL)
        send_player_pos_gui(client, gui->fd);
    return NULL;
}
