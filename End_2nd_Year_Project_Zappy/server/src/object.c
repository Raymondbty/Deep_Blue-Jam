/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** object.c
*/

#include "server.h"

void check_object(client_t *client, map_t *map, char *object, bool take_drop)
{
    char *tab[8] = {"food", "linemate", "deraumere", "sibur", "mendiane",
    "phiras", "thystame", NULL};
    void (*ptr[8])(client_t *, map_t *, bool) = {take_drop_food,
    take_drop_linemate, take_drop_deraumere, take_drop_sibur,
    take_drop_mendiane, take_drop_phiras, take_drop_thystame,
    NULL};

    for (int i = 0; tab[i]; ++i) {
        if (strcmp(tab[i], object) == 0) {
            ptr[i](client, map, take_drop);
            send_ok_ai(client->fd);
            return;
        }
    }
    send_ko_ai(client->fd);
}

void *take_drop_object(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    client_t *gui = content->gui;
    map_t *map = content->map;
    queue_t *queue = content->client->queue;
    char *object = content->command[0];
    bool take_drop = content->boulean;

    check_object(client, map, object, take_drop);
    if (gui != NULL)
        send_tile_content_gui(gui, map, client->pos.x, client->pos.y);
    free_word_array(content->command);
    return (NULL);
}
