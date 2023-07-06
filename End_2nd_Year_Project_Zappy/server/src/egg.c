/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** client_interaction.c
*/

#include "server.h"

egg_t *get_egg_from_team(team_t *team, egg_t *eggs)
{
    egg_t *tmp = eggs;

    for (; tmp != NULL; tmp = tmp->next)
        if (strcmp(tmp->team, team->name) == 0)
            return tmp;
    return NULL;
}

void set_egg(egg_t *egg, egg_t *eggs, client_t *client, map_t *map)
{
    egg->pos = client->pos;
    egg->team = strdup(client->actual_team);
    egg->time = 0;
    egg->next = eggs;
    eggs = &egg[0];
    map->tiles[client->pos.y][client->pos.x]->nbr_egg++;
}

void *end_create_egg(client_t *client, client_t *gui, egg_t *egg,
    team_t *team)
{
    team->max_clients++;
    team->nb_unused_slots++;
    team->nbr_eggs++;
    send_ok_ai(client->fd);
    if (gui != NULL) {
        send_player_egg_laying_gui(client, gui->fd);
        send_egg_laying_by_player_gui(egg, gui->fd);
    }
    return NULL;
}

void *create_egg(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    egg_t *eggs = content->list_eggs;
    queue_t *queue = content->queue;
    egg_t *egg = malloc(sizeof(egg_t));
    map_t *map = content->map;
    client_t *gui = content->gui;
    team_t **list_teams = content->teams;
    team_t *team;
    int egg_id = content->egg_id;

    if (egg == NULL)
        return NULL;
    set_egg(egg, eggs, client, map);
    egg->id = egg_id;
    egg->id_parent = client->id;
    team = get_team(egg->team, list_teams);
    end_create_egg(client, gui, egg, team);
}
