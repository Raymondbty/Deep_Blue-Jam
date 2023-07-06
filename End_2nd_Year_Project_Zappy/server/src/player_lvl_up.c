/*
** EPITECH PROJECT, 2023
** zappie
** File description:
** player_lvl_up.c
*/

#include "server.h"

client_t **get_all_client_on_tile(client_t *client, map_t *map,
client_t *list_client)
{
    client_t *tmp = list_client;
    client_t **nbr_client_on_tile = malloc(sizeof(client_t *) *
    (map->tiles[client->pos.y][client->pos.x]->nbr_player + 1));
    int nbr_client = 0;

    for (; tmp != NULL;) {
        if (tmp->pos.x == client->pos.x && tmp->pos.y == client->pos.y) {
            nbr_client_on_tile[nbr_client] = tmp;
            nbr_client++;
        }
        tmp = tmp->next;
    }
    nbr_client_on_tile[nbr_client] = NULL;
    return nbr_client_on_tile;
}

bool check_lvl_up_start(client_t **nbr_client_on_tile, client_t *client,
map_t *map, client_t *gui)
{
    if (!check_cond_lvl_up(client, map)) {
        send_ko_ai(client->fd);
        return false;
    }
    for (int i = 0; nbr_client_on_tile[i] != NULL; i++) {
        if (gui != NULL)
            send_incantation_gui(nbr_client_on_tile, nbr_client_on_tile[i]->fd);
        send_player_incantation_ai(nbr_client_on_tile[i]);
    }
    return true;
}

void check_lvl_up_end(client_t **nbr_client_on_tile, client_t *client,
map_t *map, client_t *gui)
{
    if (!check_cond_lvl_up(client, map)) {
        send_ko_ai(client->fd);
        return;
    }
    for (int i = 0; nbr_client_on_tile[i] != NULL; i++) {
        if (gui != NULL)
            send_incantation_result_gui(nbr_client_on_tile[i],
            nbr_client_on_tile[i]->fd, nbr_client_on_tile[i]->level);
        send_ok_ai(nbr_client_on_tile[i]->fd);
        nbr_client_on_tile[i]->level++;
    }
    remove_ressources_incantation(client, map);
}

void *incantation(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    map_t *map = content->map;
    client_t *list_client = content->list_clients;
    queue_t *queue = content->queue;
    client_t **nbr_client_on_tile;
    bool status = content->boulean;
    client_t *gui = content->gui;

    nbr_client_on_tile = get_all_client_on_tile(client, map, list_client);
    if (status) {
        if (!check_lvl_up_start(nbr_client_on_tile, client, map, gui))
            content->boulean = false;
    } else
        check_lvl_up_end(nbr_client_on_tile, client, map, gui);
    free(nbr_client_on_tile);
    return NULL;
}
