/*
** EPITECH PROJECT, 2023
** zappie
** File description:
** queue.c
*/

#include "server.h"

queue_t *join_queue(queue_t *first, queue_t *second)
{
    queue_t *tmp = malloc(sizeof(queue_t));

    if (tmp == NULL)
        return NULL;
    if (first == NULL && second == NULL) {
        free(tmp);
        return NULL;
    }
    if (first != NULL) {
        tmp->ptr = first->ptr;
        tmp->content = first->content;
        tmp->cd = first->cd;
        tmp->next = join_queue(first->next, second);
    } else if (second != NULL) {
        tmp->ptr = second->ptr;
        tmp->content = second->content;
        tmp->cd = second->cd;
        tmp->next = join_queue(first, second->next);
    }
    return tmp;
}

queue_t *create_queue(queue_t *queue,
void *(*ptr)(void *needed),
content_thread_command_t *content, int cd)
{
    queue_t *new = malloc(sizeof(queue_t));

    if (new == NULL)
        return NULL;
    new->ptr = ptr;
    new->next = &queue[0];
    new->content = content;
    new->cd = cd;
    return new;
}

queue_t *destroy_queue(queue_t *queue, bool destroy_content)
{
    if (queue == NULL)
        return NULL;
    queue->next = destroy_queue(queue->next, destroy_content);
    if (destroy_content)
        destroy_content_thread(queue->content);
    free(queue);
    queue = NULL;
    return queue;
}
