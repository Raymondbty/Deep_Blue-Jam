/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-mathieu.nowakowski
** File description:
** server.c
*/

#include "server.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

bool is_writable(int fd)
{
    int flag = fcntl(fd, F_GETFL);

    if (flag == -1 || !(flag & O_RDWR))
        return false;
    return true;
}

void change_max_fd(server_t *server, int fd)
{
    if (fd > server->max_fd) {
        server->max_fd = fd;
    }
}

void check_client_isset(server_t *server)
{
    int fd;
    client_t *client = server->clients;

    FD_ZERO(&server->readfds);
    FD_SET(server->fd, &server->readfds);
    server->max_fd = server->fd;
    for (int i = 0; client != NULL; i++) {
        fd = client->fd;
        if (fd > 0 && is_writable(fd)) {
            FD_SET(fd, &server->readfds);
            change_max_fd(server, fd);
        }
        client = client->next;
    }
}

void read_client(client_t *client, server_t *server)
{
    char buffer[MAX_BUFFER];
    int n;
    char **command;
    char *type;

    n = read(client->fd, buffer, MAX_BUFFER);
    if (n == 0) {
        pthread_mutex_lock(&server->client_mutex);
        type = client->type;
        server->clients = close_client(server->clients, client->id);
        if (!strcmp(type, GUI))
            server->gui = NULL;
        pthread_mutex_unlock(&server->client_mutex);
        return;
    }
    buffer[n] = '\0';
    command = my_str_to_word_array(buffer, "\n");
    for (int i = 0; command[i] != NULL; i++)
        check_command(command[i], server, client);
    return;
}
