/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** client_interaction.c
*/

#include "server.h"

void destroy_egg(egg_t *egg, egg_t *list_eggs)
{
    egg_t *tmp = list_eggs;

    if (tmp == egg) {
        list_eggs = egg->next;
        free(egg->team);
        free(egg);
        return;
    }
    while (tmp->next != NULL) {
        if (tmp->next == egg) {
            tmp->next = egg->next;
            free(egg->team);
            free(egg);
            return;
        }
        tmp = tmp->next;
    }
}

void destroy_all_egg(server_t *server)
{
    egg_t *tmp = server->eggs;
    egg_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->team);
        free(tmp);
        tmp = next;
    }
    server->eggs = NULL;
}
