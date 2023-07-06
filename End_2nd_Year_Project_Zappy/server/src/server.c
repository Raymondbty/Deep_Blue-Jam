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
#include <stdlib.h>

#include <signal.h>
#include <stdlib.h>

server_t *server;

void handle_sigint(int signo, siginfo_t *si, void *unused)
{
    if (signo == SIGINT) {
        if (server != NULL) {
            destroy_server(server);
        }
        exit(0);
    }
}

void server_loop_client(int active, server_t *server, client_t *client)
{
    if (FD_ISSET(server->fd, &server->readfds)) {
        server->clients = accept_client(server, server->clients);
        server->nb_clients++;
        server->id_client++;
        FD_SET(server->fd, &server->readfds);
    }
    check_client_isset(server);
    active = select(server->max_fd + 1, &server->readfds, NULL, NULL, NULL);
    if ((active < 0) && (errno != EINTR)) {
        perror("select");
        exit(EXIT_FAILURE);
    }
    client = server->clients;
    for (; client != NULL; client = client->next)
        if (FD_ISSET(client->fd, &server->readfds))
            read_client(client, server);
}

void server_loop(int active, server_t *server)
{
    client_t *client;
    struct sigaction sa;

    sa.sa_sigaction = handle_sigint;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    server_loop_client(active, server, client);
}

int server_main(char **argv)
{
    int active = -1;
    server = create_server(argv);

    if (server == NULL) {
        return 84;
    }
    if (server->clients != NULL) {
        printf("Error: clients list not empty\n");
        free(server->clients);
        server->clients = NULL;
    }

    if (server == NULL)
        return (84);
    bind_listen(server);
    FD_ZERO(&server->readfds);
    FD_SET(server->fd, &server->readfds);
    while (1)
        server_loop(active, server);
    return (0);
}
