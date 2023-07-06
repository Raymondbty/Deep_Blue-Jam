/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** game.c
*/

#include "server.h"

queue_t *cond_next_queue_null(client_t *client, queue_t *queue,
server_t *server)
{
    if (queue->content->list_clients != NULL)
        queue->content->list_clients = &server->clients[0];
    if (queue->content->list_eggs != NULL)
        queue->content->list_eggs = &server->eggs[0];
    if (queue->content->map != NULL)
        queue->content->map = &server->map[0];
    queue->ptr(queue->content);
    client->cd_until_next_action = queue->cd;
    if (queue->cd == 300) {
        queue->cd = 0;
        queue->content->boulean = false;
    } else {
        queue = destroy_queue(queue, true);
    }
    return queue;
}

queue_t *check_launch_commands_in_queue(client_t *client, queue_t *queue,
server_t *server)
{
    if (client->cd_until_next_action > 0)
        return queue;
    if (queue == NULL)
        return NULL;
    if (queue->next != NULL) {
        queue->next = check_launch_commands_in_queue(client, queue->next,
        server);
    } else if (queue->next == NULL && client->cd_until_next_action <= 0) {
        queue = cond_next_queue_null(client, queue, server);
    }
    return queue;
}
