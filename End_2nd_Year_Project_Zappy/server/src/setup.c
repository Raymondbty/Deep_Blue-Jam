/*
** EPITECH PROJECT, 2023
** zappie
** File description:
** setup.c
*/

#include "server.h"

void create_game(server_t *server)
{
    server->game = malloc(sizeof(game_t));

    server->game->is_running = true;
    server->game->nbr_time_pass = 0;
    server->game->nbr_regen_map = 0;
    server->game->start_time = clock();
    pthread_mutex_init(&server->client_mutex, NULL);
    pthread_create(&server->thread_game, NULL, &game, server);
}

void fill_adress_server(server_t *server)
{
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
}

server_t *create_server(char **argv)
{
    int opt = 1;
    server_t *server = parse_flags(argv);

    if (server == NULL)
        return NULL;
    if ((server->fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    fill_adress_server(server);
    create_game(server);
    server->gui = NULL;
    server->id_client = 0;
    server->id_egg = 0;
    return (server);
}

void bind_listen(server_t *server)
{
    if (bind(server->fd, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server->fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    server->max_fd = server->fd;
    server->tv.tv_sec = 0;
    server->tv.tv_usec = 0;
    server->len_server = sizeof(server->address);
}
