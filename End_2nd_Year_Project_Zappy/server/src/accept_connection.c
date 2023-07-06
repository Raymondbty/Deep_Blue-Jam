/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** accept_connection.c
*/

#include "server.h"

client_t *create_client(int fd, int id)
{
    client_t *client = malloc(sizeof(client_t) + 1);

    pthread_mutex_init(&client->queue_mutex, NULL);
    pthread_mutex_init(&client->client_mutex, NULL);
    client->fd = fd;
    client->name = "Anonymous";
    client->actual_team = NULL;
    client->id = id;
    client->pos.x = 0;
    client->pos.y = 0;
    client->type = NULL;
    client->orientation = 0;
    client->level = 1;
    client->survive_time = -1;
    client->cd_until_next_action = 0;
    client->tmp_queue = NULL;
    client->queue = NULL;
    client->next = NULL;
    return client;
}

int accept_connection(server_t *server)
{
    int serv_acc;

    if (select(server->fd + 1, &server->readfds, NULL, NULL, &server->tv) < 0) {
        perror("select failed");
        return 84;
    }
    serv_acc = accept(server->fd, (struct sockaddr*)&server->readfds,
    &server->len_server);
    if (serv_acc < 0) {
        perror("accept failed");
        return 84;
    }
    dprintf(serv_acc, "WELCOME\n");
    return serv_acc;
}

client_t *accept_client(server_t *server, client_t *client)
{
    int fd;

    if (client == NULL) {
        fd = accept_connection(server);
        pthread_mutex_lock(&server->client_mutex);
        client = create_client(fd, server->nb_clients);
        pthread_mutex_unlock(&server->client_mutex);
        return client;
    }
    client->next = accept_client(server, client->next);
    return client;
}
