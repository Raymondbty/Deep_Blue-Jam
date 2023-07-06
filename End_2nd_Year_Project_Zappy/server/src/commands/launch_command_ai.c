/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** check_command_ai.c
*/

#include "server.h"

void launch_command_ai_v5(char **command, server_t *server, client_t *client,
int j)
{
    switch (j) {
        case 8:
            client->tmp_queue = create_queue(client->tmp_queue, eject,
            create_content_thread(client, server->map, "gui egg list_clients",
            server, server->gui, server->eggs, server->clients), 7);
            break;
        case 11:
            client->tmp_queue = create_queue(client->tmp_queue, incantation,
            create_content_thread(client, server->map,
            "list_clients gui bool", server->clients, server->gui, true), 300);
            break;
        default:
            break;
    }
}

void launch_command_ai_v4(char **command, server_t *server, client_t *client,
int j)
{
    switch (j) {
        case 9:
            client->tmp_queue = create_queue(client->tmp_queue,
            take_drop_object,
            create_content_thread(client, server->map, "command bool gui",
            &command[1], true, server->gui), 7);
            break;
        case 10:
            client->tmp_queue = create_queue(client->tmp_queue,
            take_drop_object,
            create_content_thread(client, server->map, "command bool gui",
            &command[1], false, server->gui), 7);
            break;
        default:
            launch_command_ai_v5(command, server, client, j);
            break;
    }
}

void launch_command_ai_v3(char **command, server_t *server, client_t *client,
int j)
{
    switch (j) {
        case 6:
            client->tmp_queue = create_queue(client->tmp_queue,
            send_nbr_unused_slot_team,
            create_content_thread(client, server->map, "teams", server->teams),
            7);
            break;
        case 7:
            server->id_egg += 1;
            client->tmp_queue = create_queue(client->tmp_queue, create_egg,
            create_content_thread(client, server->map, "gui egg_id teams",
            server->gui, server->id_egg, server->teams), 42);
            break;
        default:
            launch_command_ai_v4(command, server, client, j);
            break;
    }
}

void launch_command_ai_v2(char **command, server_t *server, client_t *clt,
int j)
{
    switch (j) {
        case 3:
            clt->tmp_queue = create_queue(clt->tmp_queue,
            send_look_around_ai,
            create_content_thread(clt, server->map, ""), 7);
            break;
        case 4:
            clt->tmp_queue = create_queue(clt->tmp_queue,
            check_inventory, create_content_thread(clt, server->map, ""), 1);
            break;
        case 5:
            clt->tmp_queue = create_queue(clt->tmp_queue, broadcast,
            create_content_thread(clt, server->map,
            "command gui list_clients map", &command[1], server->gui,
            server->clients, server->map), 7);
            break;
        default:
            launch_command_ai_v3(command, server, clt, j);
            break;
    }
}

void launch_command_ai(char **command, server_t *server, client_t *client,
int j)
{
    switch (j) {
        case 0:
            client->tmp_queue = create_queue(client->tmp_queue, move_forward,
            create_content_thread(client, server->map, "gui", server->gui), 7);
            break;
        case 1:
            client->tmp_queue = create_queue(client->tmp_queue, turn_right,
            create_content_thread(client, server->map, "gui", server->gui), 7);
            break;
        case 2:
            client->tmp_queue = create_queue(client->tmp_queue, turn_left,
            create_content_thread(client, server->map, "gui", server->gui), 7);
            break;
        default:
            launch_command_ai_v2(command, server, client, j);
            break;
    }
}
