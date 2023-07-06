/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** client.h
*/

#ifndef ZAPPIE_CLIENT_H
    #define ZAPPIE_CLIENT_H

    #define MULTIPLIER_TIME_UNIT 126

    #include "ressources.h"
    #include "map.h"
    #include "teams.h"
    #include <pthread.h>
    #include <stdbool.h>
    #include <time.h>
    #include <stdlib.h>

    /**
    @brief Structure representing a position.
    This structure represents a position in a 2D space.
    It contains the coordinates x and y.
    @param x The x-coordinate.
    @param y The y-coordinate.
    */
    typedef struct pos_s {
    int x;
    int y;
    } pos_t;

    /**
    @brief Structure representing a queue node.
    This structure represents a node in a queue.
    It contains a function pointer ptr to a function that takes acontent
    parameter and returns a result,
    a pointer content to a structure content_thread_command_s,
    an integer cd representing a cooldown value,
    and a pointer next to the next node in the queue.
    @param ptr Function pointer to a function.
    @param content Pointer to a structure content_thread_command_s.
    @param cd Cooldown value.
    @param next Pointer to the next node in the queue.
    */
    typedef struct queue_s {
    void *(*ptr)(void *content);
    struct content_thread_command_s *content;
    int cd;
    struct queue_s *next;
    } queue_t;

    /**
    @brief Structure representing an egg.
    This structure represents an egg in the game.
    It contains an integer id representing the egg's ID,
    an integer time representing the remaining time until the egg hatches,
    a pointer team to a string representing the team that owns the egg,
    a position pos representing the egg's position,
    and a pointer next to the next egg in the list.
    @param id The egg's ID.
    @param time The remaining time until the egg hatches.
    @param team Pointer to a string representing the team that owns the egg.
    @param pos The egg's position.
    @param next Pointer to the next egg in the list.
    */
    typedef struct egg_s {
    int id;
    int id_parent;
    int time;
    char *team;
    pos_t pos;
    struct egg_s *next;
    } egg_t;

    /**
    @brief Structure representing a client
    This structure represents a client in the game
    and a pointer next to the next client in the list
    @param client_mutex Mutex for concurrent client management.
    @param queue_mutex Mutex for concurrent queue management.
    @param id The client's ID.
    @param fd The client's file descriptor.
    @param name The client's name.
    @param actual_team The client's current team.
    @param type The client's type.
    @param orientation The client's orientation.
    @param level The client's level.
    @param survive_time The remaining time the client can survive
    without food.
    @param cd_until_next_action The cooldown until the client can perform
    the next action.
    @param pos The client's position.
    @param ressources The client's resources.
    @param tmp_queue Pointer to a temporary queue of commands.
    @param queue Pointer to a queue of commands.
    @param next Pointer to the next client in the list.
    */
    typedef struct client_s {
    pthread_mutex_t client_mutex;
    pthread_mutex_t queue_mutex;

    int id;
    int fd;
    const char *name;
    char *actual_team;
    char *type;
    int orientation;
    int level;
    int survive_time;
    int cd_until_next_action;
    pos_t pos;
    ressources_t ressources;
    queue_t *tmp_queue;
    queue_t *queue;
    struct client_s *next;
    } client_t;

    /**
    @brief Structure representing the content of a thread command.
    This structure represents the content of a thread command.
    It contains pointers to various game-related structures and data,
    including the GUI client, the executing client, the list of all clients,
    the list of eggs, the map, the command queue, the teams,
    the command string, a boolean value, and an egg ID.
    @param gui Pointer to the GUI client.
    @param client Pointer to the executing client.
    @param list_clients Pointer to the list of all clients.
    @param list_eggs Pointer to the list of eggs.
    @param map Pointer to the map.
    @param queue Pointer to the command queue.
    @param teams Pointer to the array of teams.
    @param command Pointer to the command string.
    @param boulean Boolean value.
    @param egg_id Egg ID.
    */
    typedef struct content_thread_command_s {
    client_t *gui;
    client_t *client;
    client_t *list_clients;
    egg_t *list_eggs;
    map_t *map;
    queue_t *queue;
    team_t **teams;
    char **command;
    bool boulean;
    int egg_id;
    } content_thread_command_t;

    /* Client movement */

    /**
    @brief Thread function for turning the client to the right.
    This function represents a thread that rotates the client to the right.
    It takes a pointer to a data structure data as a parameter.
    The data structure should contain the necessary information to perform
    the rotation.
    The function returns a pointer to the result of the thread execution.
    @param data Pointer to the data structure.
    @return Pointer to the result of the thread execution.
    */
    void *turn_right(void *data);

    /**
    @brief Thread function for turning the client to the left.
    This function represents a thread that rotates the client to the left.
    It takes a pointer to a data structure data as a parameter.
    The data structure should contain the necessary information to perform
    the rotation.
    The function returns a pointer to the result of the thread execution.
    @param data Pointer to the data structure.
    @return Pointer to the result of the thread execution.
    */
    void *turn_left(void *data);

#endif
