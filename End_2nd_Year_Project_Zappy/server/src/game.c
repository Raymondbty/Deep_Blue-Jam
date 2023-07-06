/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** game.c
*/

#include "server.h"

team_t *check_end_game(client_t *list_client, team_t **list_teams)
{
    client_t *tmp = list_client;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->level == 8)
            return get_team(tmp->actual_team, list_teams);
    }
    return NULL;
}

void regen_ressources(map_t *map, game_t *game, client_t *gui)
{
    if (game->nbr_time_pass / 20 < game->nbr_regen_map + 1)
        return;
    generate_ressources(map, FOOD, MULTIPLIER_FOOD, map->ressources->nbr_food);
    generate_ressources(map, LINEMATE, MULTIPLIER_LINEMATE,
    map->ressources->nbr_linemate);
    generate_ressources(map, DERAUMERE, MULTIPLIER_DERAUMERE,
    map->ressources->nbr_deraumere);
    generate_ressources(map, SIBUR, MULTIPLIER_SIBUR,
    map->ressources->nbr_sibur);
    generate_ressources(map, MENDIANE, MULTIPLIER_MENDIANE,
    map->ressources->nbr_mendiane);
    generate_ressources(map, PHIRAS, MULTIPLIER_PHIRAS,
    map->ressources->nbr_phiras);
    generate_ressources(map, THYSTAME, MULTIPLIER_THYSTAME,
    map->ressources->nbr_thystame);
    game->nbr_regen_map += 1;
    if (gui != NULL)
        send_all_map_content_gui(gui, map);
}

void check_new_commands_in_queue(client_t *client)
{
    pthread_mutex_lock(&client->queue_mutex);
    if (client->tmp_queue != NULL) {
        client->queue = join_queue(client->tmp_queue, client->queue);
        client->tmp_queue = destroy_queue(client->tmp_queue, false);
    }
    pthread_mutex_unlock(&client->queue_mutex);
}

void game_loop(void *data, server_t *server, client_t *tmp)
{
    int new_nbr_time_pass =
    ((clock() - server->game->start_time) * server->freq) / CLOCKS_PER_SEC;

    pthread_mutex_lock(&server->client_mutex);
    time_pass(server->clients, new_nbr_time_pass -
    server->game->nbr_time_pass);
    pthread_mutex_unlock(&server->client_mutex);
    regen_ressources(server->map, server->game, server->gui);
    server->game->nbr_time_pass = new_nbr_time_pass;
    pthread_mutex_lock(&server->client_mutex);
    tmp = server->clients;
    for (; tmp != NULL; tmp = tmp->next) {
        pthread_mutex_lock(&tmp->client_mutex);
        check_new_commands_in_queue(tmp);
        tmp->queue = check_launch_commands_in_queue(tmp, tmp->queue, server);
        check_nbr_time_survive(tmp, server->gui);
        pthread_mutex_unlock(&tmp->client_mutex);
    }
    pthread_mutex_unlock(&server->client_mutex);
}

void *game(void *data)
{
    server_t *server = (server_t *)data;
    client_t *tmp;
    team_t *end_game;

    while (server->game->is_running) {
        game_loop(data, server, tmp);
        end_game = check_end_game(server->clients, server->teams);
        if (end_game != NULL) {
            server->game->is_running = false;
        }
    }
    if (server->gui != NULL && end_game != NULL)
        send_end_game_gui(end_game, server->gui->fd);
    return NULL;
}
