/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** content_thread_command.c
*/

#include "server.h"

char **copy_command(char **command)
{
    char **new;
    int nbr_command = 0;

    for (; command[nbr_command] != NULL; nbr_command++);
    new = malloc(sizeof(char *) * (nbr_command + 1));
    if (new == NULL)
        return NULL;
    for (int i = 0; command[i] != NULL; i++)
        new[i] = strdup(command[i]);
    new[nbr_command] = NULL;
    return new;
}

void get_new(content_thread_command_t *new, char *info, va_list ap)
{
    char **tab = my_str_to_word_array(info, " ");

    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++) {
        if (strcmp(tab[i], "gui") == 0)
            new->gui = &va_arg(ap, client_t *)[0];
        if (strcmp(tab[i], "command") == 0)
            new->command = copy_command(va_arg(ap, char **));
        if (strcmp(tab[i], "bool") == 0)
            new->boulean = va_arg(ap, int);
        if (strcmp(tab[i], "egg") == 0)
            new->list_eggs = &va_arg(ap, egg_t *)[0];
        if (strcmp(tab[i], "list_clients") == 0)
            new->list_clients = &va_arg(ap, client_t *)[0];
        if (strcmp(tab[i], "egg_id") == 0)
            new->egg_id = va_arg(ap, int);
        if (strcmp(tab[i], "teams") == 0)
            new->teams = &va_arg(ap, team_t **)[0];
    }
}

content_thread_command_t *create_content_thread(client_t *client,
map_t *map, char *info, ...)
{
    content_thread_command_t *new = malloc(sizeof(content_thread_command_t));
    va_list ap;

    if (new == NULL)
        return NULL;
    new->client = &client[0];
    new->map = &map[0];
    new->queue = &client->queue[0];
    va_start(ap, info);
    get_new(new, info, ap);
    va_end(ap);
    return new;
}

void destroy_content_thread(content_thread_command_t *content)
{
    free(content);
}
