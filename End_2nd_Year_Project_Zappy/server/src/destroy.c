/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** destroy.c
*/

#include "server.h"

void destroy_game(game_t *game, server_t *server)
{
    game->is_running = false;
    pthread_join(server->thread_game, NULL);
    free(game);
}

void destroy_server(server_t *server)
{
    destroy_game(server->game, server);
    destroy_all_egg(server);
    destroy_all_teams(server->teams);
    destroy_map(server->map);
    for (; server->clients != NULL; server->clients = server->clients->next) {
        close_client(server->clients, server->clients->id);
    }
    if (server->buffer != NULL)
        free(server->buffer);
    pthread_mutex_destroy(&server->client_mutex);
    close(server->fd);
    free(server);
}
