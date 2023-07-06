/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-mathieu.nowakowski
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #include <stdarg.h>

    #include "include.h"
    #include "client.h"
    #include "utils.h"

    /**

    * @brief
    * Max size of buffer for communications

    */
    #define MAX_BUFFER 1024
    /**

    * @brief
    * Speed of time spent in the game

    */
    #define DEFAULT_FREQ 100


    /**
    @brief Structure representing game information.
    This structure allows saving information related to a game.
    @param is_running Indicates whether the game is currently running.
    @param nbr_time_pass The number of times time has passed.
    @param nbr_regen_map The number of map regenerations.
    @param start_time The game's start time. ??

    */
    typedef struct game_s {
        bool is_running;
        int nbr_regen_map;
        clock_t nbr_time_pass;
        clock_t start_time;
    } game_t;

    /**

     @brief
    Structure representing a game server.
    This structure contains the necessary information for managing a game
    server.
    @param client_mutex Mutex for concurrent client management.
    @param thread_game Game thread.
    @param fd File descriptor for the server socket.
    @param max_fd Maximum file descriptor for connection monitoring.
    @param port Port used by the server.
    @param buffer Read/write buffer.
    @param len_server Length of the server.
    @param freq Game refresh frequency.
    @param nb_teams Number of teams.
    @param nb_clients Number of connected clients.
    @param id_client ID of the next client to connect.
    @param id_egg ID of the next egg to create.
    @param game Pointer to the game structure (see description below).
    @param gui Pointer to the GUI client (graphical interface).
    @param clients Array of connected clients.
    @param eggs Array of eggs present on the map.
    @param map Pointer to the map structure.
    @param teams Array of teams.
    @param readfds Set of file descriptors for reading.
    @param address Address structure for the server.
    @param tv Time structure for select().
    */
    typedef struct server_s {
        pthread_mutex_t client_mutex;
        pthread_t thread_game;

        int fd;
        int max_fd;
        int port;
        char *buffer;
        unsigned int len_server;
        float freq;
        int nb_teams;
        int nb_clients;
        int id_client;
        int id_egg;
        game_t *game;
        client_t *gui;
        client_t *clients;
        egg_t *eggs;
        map_t *map;
        team_t **teams;
        fd_set readfds;
        struct sockaddr_in address;
        struct timeval tv;
    } server_t;

    /* Network Functions */

    /**
    @brief Main function of the server.
    This function is the main entry point of the server.
    It takes an array of character strings argv as a parameter,
    which contains the command line arguments. The function returns
    an integer representing the server's exit status.
    @param argv Array of character strings representing the command line
    arguments.
    @return An integer representing the server's exit status.
    */
    int server_main(char **argv);

    /**
    @brief Create a server.
    This function creates and initializes an instance of the server_t
    structure.
    It takes an array of character strings argv as a parameter, which contains
    the command line arguments for configuring the server.
    The function returns a pointer to the newly created server_t structure,
    or NULL in case of error.
    @param argv Array of character strings representing the command line
    arguments.
    @return A pointer to the newly created server_t structure, or NULL in
    case of error.
    */
    server_t *create_server(char **argv);

    /**

    * @brief Accepts a client.
    *
    * This function allows accepting a client connection on the server.
    * It takes a pointer to the server_t structure representing the server,
    * and a pointer to the existing client structure client_t.
    * The function returns a pointer to the updated client_t structure with
    * the information of the new client.
    *
    * @param server A pointer to the server_t structure representing
    * the server.
    * @param client A pointer to the existing client_t structure representing
    * the client.
    * @return A pointer to the updated client_t structure with the information
    * of the new client,
    * or NULL in case of an error.
    */
    client_t *accept_client(server_t *server, client_t *client);


    /* read client Functions */

    /**

    * @brief Reads data from a client.
    *
    * This function allows reading data sent by a client.
    * It takes a pointer to the client_t structure representing the client
    * and a pointer to the server_t structure representing the server.
    * The function returns a pointer to the updated client_t structure
    * with the read data,
    * or NULL in case of an error.
    *
    * @param client A pointer to the client_t structure representing
    * the client.
    * @param server A pointer to the server_t structure representing
    * the server.
    * @return A pointer to the updated client_t structure with the read data,
    * or NULL in case of an error.
    */
    void read_client(client_t *client, server_t *server);

    /**

    * @brief Checks if clients are ready to be read.
    *
    * This function checks if clients are ready to be read.
    * It takes a pointer to the server_t structure representing the server.
    * The function does not return any value.
    *
    * @param server A pointer to the server_t structure representing
    * the server.
    */
    void check_client_isset(server_t *server);

    /**

    * @brief Modifies the maximum value of the file descriptor.
    *
    * This function modifies the maximum value of the file descriptor
    * monitored by the server.
    * It takes a pointer to the server_t structure representing the server
    * and an integer fd representing the new maximum value of the file
    * descriptor.
    * The function does not return any value.
    *
    * @param server A pointer to the server_t structure representing
    * the server.
    * @param fd The new maximum value of the file descriptor.
    */
    void change_max_fd(server_t *server, int fd);

    /**

     * @brief Gets the value of a flag.
     *
     * This function allows obtaining the value of a flag specified
     * in the command-line arguments.
     * It takes an array of strings `argv` representing
     * the command-line arguments
     * and a string `flag` representing the flag whose value is
     * to be obtained.
     * The function returns an integer representing the value of
     * the flag if found, or -1 if not found.
     *
     * @param argv Array of strings representing the command-line arguments.
     * @param flag String representing the flag whose value is to be obtained.
     * @return An integer representing the value of the flag
     * if found, or -1 if not found.
     */
    int get_flag(char **argv, char *flag);

    /**

    * @brief Gets the team names from the command-line arguments.
    *
    * This function allows obtaining the team names from the
    * command-line arguments.
    * It takes an array of strings argv representing the command-line
    * arguments
    * and an integer max_clients representing the maximum number of clients.
    * The function returns an array of pointers to team_t structures
    * containing the team names,
    * or NULL in case of an error.
    *
    * @param argv Array of strings representing the command-line arguments.
    * @param max_clients Maximum number of clients.
    * @return An array of pointers to team_t structures
    * containing the team names,
    * or NULL in case of an error.
    */
    team_t **get_teams_names(char **argv, int max_clients);

    /**

    * @brief Performs the bind and listen on the server socket.
    *
    * This function performs the bind and listen steps on the server socket.
    * It takes a pointer to the server_t structure representing the server.
    * The function does not return any value.
    *
    * @param server A pointer to the server_t structure
    * representing the server.
    */
    void bind_listen(server_t *server);

    /**
    * @brief Parses the flags and command-line arguments.
    *
    * This function parses the flags and command-line arguments,
    * and creates and initializes an instance of the server_t structure
    * with the corresponding values.
    * It takes an array of strings argv representing the command-line
    * arguments.
    * The function returns a pointer to the newly created and
    * initialized server_t structure,
    * or NULL in case of an error.
    *
    * @param argv Array of strings representing the command-line arguments.
    * @return A pointer to the newly created and initialized
    * server_t structure,
    * or NULL in case of an error.
    */
    server_t *parse_flags(char **argv);

    /**

    * @brief Handles errors during the parsing of flags and
    command-line arguments.
    *
    * This function is called in case of an error during the parsing
    * of flags and command-line arguments.
    * It displays an error message specified by the string error
    * and performs cleanup operations if necessary.
    * It takes a string error representing the error message and a
    * pointer to the server_t structure representing the server.
    * The function returns a pointer to the updated server_t structure,
    * or NULL in case of an error.
    *
    * @param error String representing the error message.
    * @param server A pointer to the server_t structure representing
    * the server.
    * @return A pointer to the updated server_t structure, or NULL in
    * case of an error.
    */
    server_t *error_parse(char *error, server_t *server);

    /* destroy function */

    /**
    @brief Destroys the game structure and frees the associated memory.
    This function destroys the game structure (game_t) and frees the
    associated memory.
    It takes a pointer to the game_t structure representing the game
    and a pointer to the server_t structure representing the server.
    The function does not return any value.
    @param game A pointer to the game_t structure representing the game.
    @param server A pointer to the server_t structure representing the server.
    */
    void destroy_game(game_t *game, server_t *server);

    /**
    * @brief Destroys the server structure and frees the associated memory.
    *
    * This function destroys the server structure (server_t) and frees
    * the associated memory.
    * It takes a pointer to the server_t structure representing the server.
    * The function does not return any value.
    *
    * @param server A pointer to the server_t structure representing
    * the server.
    */
    void destroy_server(server_t *server);


    /* Manage Client */

    /**
    @brief Gets the name of the client corresponding to the specified ID.
    This function allows getting the name of the client corresponding
    to the specified ID.
    It takes a pointer to the client_t structure representing the clients,
    and an integer id representing the ID of the desired client.
    The function returns a pointer to the client_t structure corresponding
    to the found client,
    or NULL if no matching client is found.
    @param client A pointer to the client_t structure representing
    the clients.
    @param id The ID of the desired client.
    @return A pointer to the client_t structure corresponding to the
    found client, or NULL if no matching client is found.
    */
    client_t *get_client_name(client_t *client, int id);

    /**
    @brief Closes the client corresponding to the specified ID.
    This function closes the client corresponding to the specified ID by
    setting its state to closed.
    It takes a pointer to the client_t structure representing the clients,
    and an integer id representing the ID of the client to close.
    The function returns a pointer to the updated client_t structure,
    or NULL if no matching client is found.
    @param client A pointer to the client_t structure representing
    the clients.
    @param id The ID of the client to close.
    @return A pointer to the updated client_t structure, or NULL
    if no matching client is found.
    */
    client_t *close_client(client_t *client, int id);

    /**
    @brief Closes the connection of the client corresponding to the
    specified file descriptor.
    This function closes the connection of the client corresponding to
    the specified file descriptor.
    It takes a pointer to the client_t structure representing the clients,
    and an integer fd representing the file descriptor of the client to close.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the
    clients.
    @param gui The GUI to send the information that the client is dead.
    */
    void kill_client(client_t *client, client_t *gui);

    /**
    @brief Spawns a new client on the map.
    This function spawns a new client on the map.
    It takes a pointer to the client_t structure representing the clients,
    a pointer to the map_t structure representing the map,
    and a pointer to the server_t structure representing the server.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the
    clients.
    @param map A pointer to the map_t structure representing the map.
    @param server A pointer to the server_t structure representing the server.
    @param pos The position of the client.
    */
    void spawn_client(client_t *client, map_t *map, server_t *server,
    egg_t *egg);

    /**
    @brief Reduces the client's remaining life time by the specified value.
    This function reduces the client's remaining life time by the specified
    value.
    It takes a pointer to the client_t structure representing the client
    and an integer time representing the value to reduce from the life time.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the client.
    @param time The value to reduce from the life time.
    */
    void reduce_life_time(client_t *client, int time);


    /* Manage teams */

    /**
    @brief Creates teams based on the command-line arguments.
    This function creates teams based on the command-line arguments.
    It takes an array of strings argv representing the command-line arguments,
    an array of pointers to team_t structures teams representing the existing
    teams,
    and an integer max_clients representing the maximum number of clients.
    The function returns an array of pointers to team_t structures containing
    the created and existing teams,
    or NULL in case of an error.
    @param argv Array of strings representing the command-line arguments.
    @param teams Array of pointers to team_t structures representing
    the existing teams.
    @param max_clients Maximum number of clients.
    @return An array of pointers to team_t structures containing
    the created and existing teams,
        or NULL in case of an error.
    */

    team_t **create_teams(char **argv, team_t **teams, int max_clients);

    /**
    @brief Gets the team corresponding to the specified name.
    This function gets the team corresponding to the specified name.
    It takes a string name representing the name of the desired team,
    and an array of pointers to team_t structures teams representing
    the existing teams.
    The function returns a pointer to the team_t structure corresponding
    to the found team,
    or NULL if no matching team is found.
    @param name String representing the name of the desired team.
    @param teams Array of pointers to team_t structures representing
    the existing teams.
    @return A pointer to the team_t structure corresponding to the found team,
    or NULL if no matching team is found.
    */
    team_t *get_team(char *name, team_t **teams);

    /* Check commands */

    /**
    @brief Checks a specified command and performs corresponding actions.
    This function checks a specified command and performs corresponding
    actions.
    It takes a string command representing the command to check,
    a pointer to the server_t structure representing the server,
    and a pointer to the client_t structure representing the client.
    The function does not return any value.
    @param command String representing the command to check.
    @param server A pointer to the server_t structure representing the server.
    @param client A pointer to the client_t structure representing the client.
    */
    void check_command(char *command, server_t *server, client_t *client);
    /* Communication to GUI */

    /**
    @brief Sends a message indicating that a player has laid an egg to the GUI.
    This function sends a message to the GUI indicating that a player has
    laid an egg.
    It takes a pointer to the client_t structure representing the player
    client,
    a pointer to the egg_t structure representing the egg, and a file
    descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the
    player client.
    @param egg A pointer to the egg_t structure representing the egg.
    @param fd The file descriptor.
    */
    void send_egg_laying_by_player_gui(egg_t *egg, int fd);
    void send_all_eggs_gui(egg_t *egg, int fd);

    /**
    @brief Sends a message indicating that a player has connected to an
    egg to the GUI.
    This function sends a message to the GUI indicating that a player has
    connected to an egg.
    It takes a pointer to the egg_t structure representing the egg and a
    file descriptor fd.
    The function does not return any value.
    @param egg A pointer to the egg_t structure representing the egg.
    @param fd The file descriptor.
    */
    void send_player_connect_to_egg_gui(egg_t *egg, int fd);

    /**
    @brief Sends a message indicating that an egg has died to the GUI.
    This function sends a message to the GUI indicating that an egg has died.
    It takes a pointer to the egg_t structure representing the egg and a
    file descriptor fd.
    The function does not return any value.
    @param egg A pointer to the egg_t structure representing the egg.
    @param fd The file descriptor.
    */
    void send_egg_death_gui(egg_t *egg, int fd);

    /**
    @brief Sends the size of the map to the GUI.
    This function sends the size of the map to the GUI.
    It takes a pointer to the client_t structure representing the client,
    a pointer to the map_t structure representing the map, and a file
    descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the client.
    @param map A pointer to the map_t structure representing the map.
    @param fd The file descriptor.
    */
    void send_map_size_gui(client_t *client, map_t *map);

    /**
    @brief Sends the content of a tile to the GUI.
    This function sends the content of a tile to the GUI.
    It takes a pointer to the client_t structure representing the client,
    a pointer to the map_t structure representing the map,
    and the coordinates (x, y) of the tile.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the client.
    @param map A pointer to the map_t structure representing the map.
    @param x The x-coordinate of the tile.
    @param y The y-coordinate of the tile.
    */
    void send_tile_content_gui(client_t *client, map_t *map, int x, int y);

    /**
    @brief Sends the content of the entire map to the GUI.
    This function sends the content of the entire map to the GUI.
    It takes a pointer to the client_t structure representing the client
    and a pointer to the map_t structure representing the map.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the client.
    @param map A pointer to the map_t structure representing the map.
    */
    void send_all_map_content_gui(client_t *client, map_t *map);

    /**
    @brief Sends an "expulse" message to the GUI.
    This function sends an "expulse" message to the GUI.
    It takes a pointer to the client_t structure representing the client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the client.
    @param fd The file descriptor.
    */
    void send_expulse_gui(client_t *client, int fd);

    /**
    @brief Sends a broadcast message to the GUI.
    This function sends a broadcast message to the GUI.
    It takes a pointer to the client_t structure representing the client,
    a file descriptor fd, and a message msg.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the client.
    @param fd The file descriptor.
    @param msg The message to send.
    */
    void send_broadcast_gui(client_t *client, int fd, char *msg);

    /**
    @brief Sends the position of the player to the GUI.
    This function sends the position of the player to the GUI.
    It takes a pointer to the client_t structure representing
    the player client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    */
    void send_player_pos_gui(client_t *client, int fd);
    void send_pos_all_player(client_t *client, int fd);

    /**
    @brief Sends the level of the player to the GUI.
    This function sends the level of the player to the GUI.
    It takes a pointer to the client_t structure representing
    the player client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    */
    void send_player_level_gui(client_t *client, int fd);

    /**
    @brief Sends the inventory of the player to the GUI.
    This function sends the inventory of the player to the GUI.
    It takes a pointer to the client_t structure representing
    the player client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    */
    void send_player_inventory_gui(client_t *client, int fd);

    /**
    @brief Sends an "incantation" message to the GUI.
    This function sends an "incantation" message to the GUI.
    It takes an array of pointers to the client_t structures
    representing the clients,
    and a file descriptor fd.
    The function does not return any value.
    @param clients An array of pointers to the client_t structures
    representing the clients.
    @param fd The file descriptor.
    */
    void send_incantation_gui(client_t **clients, int fd);

    /**
    @brief Sends the result of an "incantation" to the GUI.
    This function sends the result of an "incantation" to the GUI.
    It takes a pointer to the client_t structure representing
    the player client,
    a file descriptor fd, and the result of the incantation.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    @param result The result of the incantation.
    */
    void send_incantation_result_gui(client_t *client, int fd, int result);

    /**
    @brief Sends a "connection" message to the GUI.
    This function sends a "connection" message to the GUI.
    It takes a pointer to the client_t structure representing
    the player client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    */
    void send_connection_player_gui(client_t *client, int fd);

    /**
    @brief Sends a message indicating that a player has laid an egg
    to the GUI.
    This function sends a message to the GUI indicating that a player
    has laid an egg.
    It takes a pointer to the client_t structure representing
    the player client,
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    */
    void send_player_egg_laying_gui(client_t *client, int fd);

    /**
    @brief Sends a message indicating that a player has dropped resources
    to the GUI.
    This function sends a message to the GUI indicating that a player
    has dropped resources.
    It takes a pointer to the client_t structure representing
    the player client,
    a file descriptor fd, and the number of resources dropped.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the player
    client.
    @param fd The file descriptor.
    @param nbr_resources The number of resources dropped.
    */
    void send_player_drop_resources_gui(client_t *client, int fd,
    int nbr_resources);

    /**
    @brief Sends a message indicating that a player has collected resources
    to the GUI.
    This function sends a message to the GUI indicating that a player has
    collected resources.
    It takes a pointer to the client_t structure representing the player
    client,
    a file descriptor fd, and the number of resources collected.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the
    player client.
    @param fd The file descriptor.
    @param nbr_resources The number of resources collected.
    */
    void send_player_collect_resources_gui(client_t *client, int fd,
    int nbr_resources);

    /**
    @brief Sends a message indicating that a player has died to the GUI.
    This function sends a message to the GUI indicating that a player
    has died.
    It takes a pointer to the client_t structure representing the player
    client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the
    player client.
    @param fd The file descriptor.
    */
    void send_player_death_gui(client_t *client, int fd);

    /**
    @brief Sends a message indicating the end of the game to the GUI.
    This function sends a message to the GUI indicating the end of the game.
    It takes a pointer to the team_t structure representing the winning team
    and a file descriptor fd.
    The function does not return any value.
    @param team A pointer to the team_t structure representing
    the winning team.
    @param fd The file descriptor.
    */
    void send_end_game_gui(team_t *team, int fd);

    /**
    @brief Sends a message from the server to the GUI.
    This function sends a message from the server to the GUI.
    It takes a string msg representing the message
    and a file descriptor fd.
    The function does not return any value.
    @param msg The message to send.
    @param fd The file descriptor.
    */
    void send_message_from_server_gui(char *msg, int fd);

    /**
    @brief Sends a message indicating an unknown command to the GUI.
    This function sends a message to the GUI indicating that an unknown
    command was received.
    It takes a file descriptor fd.
    The function does not return any value.
    @param fd The file descriptor.
    */
    void send_unknown_command_gui(int fd);

    /**
    @brief Sends a message indicating a command parameter error to the GUI.
    This function sends a message to the GUI indicating an error with a
    command parameter.
    It takes a file descriptor fd.
    The function does not return any value.
    @param fd The file descriptor.
    */
    void send_command_parameter_gui(int fd);

    /**
    @brief Sends information about the teams to the GUI.
    This function sends information about the teams to the GUI.
    It takes a pointer to the client_t structure representing the client,
    and an array of pointers to the team_t structures representing the teams.
    The function does not return any value.
    @param client A pointer to the client_t structure representing the client.
    @param teams An array of pointers to the team_t structures
    representing the teams.
    */
    void send_teams_info_gui(client_t *client, team_t **teams);

    /**
    @brief Sends time information to the GUI.
    This function sends time information to the GUI.
    It takes a file descriptor fd and a float time representing
    the time value.
    The function does not return any value.
    @param fd The file descriptor.
    @param time The time value.
    */
    void send_time_info_gui(int fd, float time);

    /**
    @brief Sends a time modification message to the GUI.
    This function sends a message to the GUI indicating a time modification.
    It takes a file descriptor fd and a float time representing
    the modified time value.
    The function does not return any value.
    @param fd The file descriptor.
    @param time The modified time value.
    */
    void send_time_modification_gui(int fd, float time);

    /* Communication AI */

    /**
    @brief Sends an "OK" message to the AI.
    This function sends an "OK" message to the AI.
    It takes a file descriptor fd.
    The function does not return any value.
    @param fd The file descriptor.
    */
    void send_ok_ai(int fd);

    /**
    @brief Sends a "KO" message to the AI.
    This function sends a "KO" message to the AI.
    It takes a file descriptor fd.
    The function does not return any value.
    @param fd The file descriptor.
    */
    void send_ko_ai(int fd);

    /**
    @brief Sends a "look around" message to the AI.
    This function sends a "look around" message to the AI.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *send_look_around_ai(void *data);

    /**
    @brief Sends the inventory of the player to the AI.
    This function sends the inventory of the player to the AI.
    It takes a pointer to the client_t structure representing the
    player client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    */
    void send_player_inventory_ai(client_t *client);

    /**
    @brief Sends a message indicating that a player has died to the AI.
    This function sends a message to the AI indicating that a player
    has died.
    It takes a pointer to the client_t structure representing
    the player client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    */
    void send_player_death_ai(client_t *client);

    /**
    @brief Sends a message indicating that a player is performing an
    incantation to the AI.
    This function sends a message to the AI indicating that a player
    is performing an incantation.
    It takes a pointer to the client_t structure representing
    the player client
    and a file descriptor fd.
    The function does not return any value.
    @param client A pointer to the client_t structure representing
    the player client.
    @param fd The file descriptor.
    */
    void send_player_incantation_ai(client_t *client);


    /* Command redirect to ai */

    /**
    @brief Broadcasts a message to all players in the game.
    This function broadcasts a message to all players in the game.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *broadcast(void *data);

    /**
    @brief Ejects players from a tile in the game.
    This function ejects players from a tile in the game.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *eject(void *data);

    /**
    @brief Checks the inventory of a player in the game.
    This function checks the inventory of a player in the game.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *check_inventory(void *data);

    /**
    @brief Sends the number of unused slots in a team to the
    requesting player.
    This function sends the number of unused slots in a team
    to the requesting player.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *send_nbr_unused_slot_team(void *data);

    /* Check function for the send to gui */

    /**
    @brief Checks a command received from the GUI and performs the
    corresponding actions.
    This function checks a command received from the GUI and performs
    the corresponding actions.
    It takes a pointer to a string array command representing the command,
    a pointer to the server_t structure representing the server,
    and a pointer to the client_t structure representing the client.
    The function does not return any value.
    @param command A pointer to a string array representing the command.
    @param server A pointer to the server_t structure representing the server.
    @param client A pointer to the client_t structure representing the client.
    */
    void check_command_gui(char **command, server_t *server,
    client_t *client);


    /* Check function for the send to ai */

    /**
    @brief Checks a command received from an AI and performs the
    corresponding actions.
    This function checks a command received from an AI and performs the
    corresponding actions.
    It takes a pointer to a string array command representing the command,
    a pointer to the server_t structure representing the server,
    and a pointer to the client_t structure representing the AI client.
    The function does not return any value.
    @param command A pointer to a string array representing the command.
    @param server A pointer to the server_t structure representing the server.
    @param client A pointer to the client_t structure representing the AI
    client.
    */
    void check_command_ai(char **command, server_t *server, client_t *client);

    /* Check launch command ai */

    /**
    @brief Launches a command for an AI client.
    This function launches a command for an AI client.
    It takes a pointer to a string array command representing the command,
    a pointer to the server_t structure representing the server,
    a pointer to the client_t structure representing the AI client,
    and an integer j representing the index of the AI client.
    The function does not return any value.
    @param command A pointer to a string array representing the command.
    @param server A pointer to the server_t structure representing the server.
    @param client A pointer to the client_t structure representing the
    AI client.
    @param j The index of the AI client.
    */
    void launch_command_ai(char **command, server_t *server, client_t *client,
    int j);

    /**
    @brief Launches a command for an AI client (version 2).
    This function launches a command for an AI client (version 2).
    It takes a pointer to a string array command representing the command,
    a pointer to the server_t structure representing the server,
    a pointer to the client_t structure representing the AI client,
    and an integer j representing the index of the AI client.
    The function does not return any value.
    @param command A pointer to a string array representing the command.
    @param server A pointer to the server_t structure representing the server.
    @param client A pointer to the client_t structure representing the
    AI client.
    @param j The index of the AI client.
    */
    void launch_command_ai_v2(char **command, server_t *server,
    client_t *client, int j);

    /**
    @brief Launches a command for an AI client (version 3).
    This function launches a command for an AI client (version 3).
    It takes a pointer to a string array command representing the command,
    a pointer to the server_t structure representing the server,
    a pointer to the client_t structure representing the AI client,
    and an integer j representing the index of the AI client.
    The function does not return any value.
    @param command A pointer to a string array representing the command.
    @param server A pointer to the server_t structure representing the server.
    @param client A pointer to the client_t structure representing the AI
    client.
    @param j The index of the AI client.
    */
    void launch_command_ai_v3(char **command, server_t *server,
    client_t *client, int j);

    /**
    @brief Launches a command for an AI client (version 4).
    This function launches a command for an AI client (version 4).
    It takes a pointer to a string array command representing the command,
    a pointer to the server_t structure representing the server,
    a pointer to the client_t structure representing the AI client,
    and an integer j representing the index of the AI client.
    The function does not return any value.
    @param command A pointer to a string array representing the command.
    @param server A pointer to the server_t structure representing the server.
    @param client A pointer to the client_t structure representing the AI
    client.
    @param j The index of the AI client.
    */
    void launch_command_ai_v4(char **command, server_t *server,
    client_t *client, int j);

    /**
    @brief Launches a command for an AI client (version 5).
    This function launches a command for an AI client (version 5).
    It takes a pointer to a string array command representing the command,
    a pointer to the server_t structure representing the server,
    a pointer to the client_t structure representing the AI client,
    and an integer j representing the index of the AI client.
    The function does not return any value.
    @param command A pointer to a string array representing the command.
    @param server A pointer to the server_t structure representing the server.
    @param client A pointer to the client_t structure representing the AI
    client.
    @param j The index of the AI client.
    */
    void launch_command_ai_v5(char **command, server_t *server,
    client_t *client, int j);

    /* Player movement */

    /**
    @brief Moves a player forward in the game.
    This function moves a player forward in the game.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *move_forward(void *data);

    /* Map info */

    /**
    @brief Finds a player on a specific tile.
    This function finds a player on a specific tile.
    It takes a pointer to the all_clients (list of all clients) and a pointer
    to the client (current client) as arguments.
    The function returns a pointer to the client_t structure representing the
    player found, or NULL if no player is found.
    @param all_clients A pointer to the list of all clients.
    @param client A pointer to the current client.
    @return A pointer to the client_t structure representing the player found,
    or NULL if no player is found.
    */
    client_t *find_player_on_tile(client_t *all_clients, client_t *client);

    /**
    @brief Finds an egg on a specific tile.
    This function finds an egg on a specific tile.
    It takes a pointer to the eggs (list of all eggs) and a pos (position)
    as arguments.
    The function returns a pointer to the egg_t structure representing the
    egg found, or NULL if no egg is found.
    @param eggs A pointer to the list of all eggs.
    @param pos The position of the tile to search for an egg.
    @return A pointer to the egg_t structure representing the egg found,
    or NULL if no egg is found.
    */
    egg_t *find_egg_on_tile(egg_t *eggs, pos_t pos);

    /* The game */

    /**
    @brief Runs the game logic.
    This function runs the game logic.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *game(void *data);

    /**
    @brief Creates an egg.
    This function creates an egg.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *create_egg(void *data);

    /**
    @brief Gets an egg from a team.
    This function gets an egg from a team.
    It takes a pointer to the team (team structure) and a pointer
    to the eggs (list of all eggs) as arguments.
    The function returns a pointer to the egg_t structure representing
    the egg found, or NULL if no egg is found.
    @param team A pointer to the team structure.
    @param eggs A pointer to the list of all eggs.
    @return A pointer to the egg_t structure representing the egg found,
    or NULL if no egg is found.
    */
    egg_t *get_egg_from_team(team_t *team, egg_t *eggs);

    /**
    @brief Destroys an egg.
    This function destroys an egg.
    It takes a pointer to the egg (egg structure) and a pointer to the
    list_eggs (list of all eggs) as arguments.
    The function does not return any value.
    @param egg A pointer to the egg structure.
    @param list_eggs A pointer to the list of all eggs.
    */
    void destroy_egg(egg_t *egg, egg_t *list_eggs);

    /**
    @brief Destroys all eggs.
    This function destroys all eggs.
    It takes a pointer to the server (server structure) as an argument.
    The function does not return any value.
    @param server A pointer to the server structure.
    */
    void destroy_all_egg(server_t *server);

    /**
    @brief Performs the "look" action for a client.
    This function performs the "look" action for a client.
    It takes a pointer to the client (client structure) and a pointer
    to the map (map structure) as arguments.
    The function returns a pointer to a 2D array of tile_t structures
    representing the visible tiles.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @return A pointer to a 2D array of tile_t structures representing
    the visible tiles.
    */
    tile_t **look(client_t *client, map_t *map);

    /**
    @brief Performs the incantation action.
    This function performs the incantation action.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *incantation(void *data);

    /**
    @brief Checks the conditions for a player to level up.
    This function checks the conditions for a player to level up.
    It takes a pointer to the client (client structure) and a pointer
    to the map (map structure) as arguments.
    The function returns a boolean value indicating whether the
    conditions are met (true) or not (false).
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @return A boolean value indicating whether the conditions are met
    (true) or not (false).
    */
    bool check_cond_lvl_up(client_t *client, map_t *map);

    /**
    @brief Checks the conditions for a player to level up (version 2).
    This function checks the conditions for a player to level up (version 2).
    It takes a pointer to the client (client structure) and a pointer
    to the map (map structure) as arguments.
    The function returns a boolean value indicating whether the conditions
    are met (true) or not (false).
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @return A boolean value indicating whether the conditions
    are met (true) or not (false).
    */
    bool check_cond_lvl_up_v2(client_t *client, map_t *map);

    /**
    @brief Checks the conditions for a player to level up (version 3).
    This function checks the conditions for a player to level up (version 3).
    It takes a pointer to the client (client structure) and a pointer to
    the map (map structure) as arguments.
    The function returns a boolean value indicating whether
    the conditions are met (true) or not (false).
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @return A boolean value indicating whether the conditions are met
    (true) or not (false).
    */
    bool check_cond_lvl_up_v3(client_t *client, map_t *map);

    /**
    @brief Advances the game time for a client.
    This function advances the game time for a client.
    It takes a pointer to the client (client structure) and an integer
    time_pass representing the time to advance.
    The function returns the updated time value.
    @param client A pointer to the client structure.
    @param time_pass The time to advance.
    */
    void time_pass(client_t *client, clock_t time_pass);

    /**
    @brief Checks the number of times a client has survived and
    informs the GUI.
    This function checks the number of times a client has survived
    and informs the GUI.
    It takes a pointer to the client (client structure) and a pointer
    to the gui (client structure representing the GUI) as arguments.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param gui A pointer to the client structure representing the GUI.
    */
    void check_nbr_time_survive(client_t *client, client_t *gui);

    /* Take/Drop object */

    /**
    @brief Performs the take/drop object action.
    This function performs the take/drop object action.
    It takes a pointer to the data (data structure) as an argument.
    The function returns a void* pointer.
    @param data A pointer to the data structure.
    @return A void* pointer.
    */
    void *take_drop_object(void *data);

    /**
    @brief Takes or drops food.
    This function takes or drops food for a client.
    It takes a pointer to the client (client structure), a pointer
    to the map (map structure),
    and a boolean take_drop indicating whether to take or drop the food.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @param take_drop A boolean indicating whether to take or drop the food.
    */
    void take_drop_food(client_t *client, map_t *map, bool take_drop);

    /**
    @brief Takes or drops linemate.
    This function takes or drops linemate for a client.
    It takes a pointer to the client (client structure), a pointer
    to the map (map structure),
    and a boolean take_drop indicating whether to take or drop the linemate.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @param take_drop A boolean indicating whether to take or drop
    the linemate.
    */
    void take_drop_linemate(client_t *client, map_t *map, bool take_drop);

    /**
    @brief Takes or drops deraumere.
    This function takes or drops deraumere for a client.
    It takes a pointer to the client (client structure),
    a pointer to the map (map structure),
    and a boolean take_drop indicating whether to take or drop the deraumere.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @param take_drop A boolean indicating whether to take
    or drop the deraumere.
    */
    void take_drop_deraumere(client_t *client, map_t *map, bool take_drop);

    /**
    @brief Takes or drops sibur.
    This function takes or drops sibur for a client.
    It takes a pointer to the client (client structure),
    a pointer to the map (map structure),
    and a boolean take_drop indicating whether to take or drop the sibur.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @param take_drop A boolean indicating whether to take or drop the sibur.
    */
    void take_drop_sibur(client_t *client, map_t *map, bool take_drop);

    /**
    @brief Takes or drops mendiane.
    This function takes or drops mendiane for a client.
    It takes a pointer to the client (client structure),
    a pointer to the map (map structure),
    and a boolean take_drop indicating whether to
    take or drop the mendiane.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @param take_drop A boolean indicating whether to
    take or drop the mendiane.
    */
    void take_drop_mendiane(client_t *client, map_t *map, bool take_drop);

    /**
    @brief Takes or drops phiras.
    This function takes or drops phiras for a client.
    It takes a pointer to the client (client structure),
    a pointer to the map (map structure),
    and a boolean take_drop indicating whether to take or drop the phiras.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @param take_drop A boolean indicating whether to take or drop the phiras.
    */
    void take_drop_phiras(client_t *client, map_t *map, bool take_drop);

    /**
    @brief Takes or drops thystame.
    This function takes or drops thystame for a client.
    It takes a pointer to the client (client structure), a pointer
    to the map (map structure),
    and a boolean take_drop indicating whether to take or drop the thystame.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @param take_drop A boolean indicating whether to take or drop
    the thystame.
    */
    void take_drop_thystame(client_t *client, map_t *map, bool take_drop);

    /* Content thread command (actually the bin of prototype) */

    /**
    @brief Creates a queue with the specified parameters.
    This function creates a queue with the specified parameters.
    It takes a pointer to the queue (queue structure),
    a function pointer ptr representing the thread function,
    a pointer to the content (content_thread_command_t structure),
    and an integer cd representing the cooldown.
    The function returns a pointer to the created queue.
    @param queue A pointer to the queue structure.
    @param ptr A function pointer representing the thread function.
    @param content A pointer to the content_thread_command_t structure.
    @param cd The cooldown value.
    @return A pointer to the created queue.
    */
    queue_t *create_queue(queue_t *queue, void *(*ptr)(void *needed),
    content_thread_command_t *content, int cd);

    /**
    @brief Creates a content_thread_command_t structure with the specified
    parameters.
    This function creates a content_thread_command_t structure with the
    specified parameters.
    It takes a pointer to the client (client structure),
    a pointer to the map (map structure),
    a string info representing additional information,
    and variadic arguments ... for additional parameters.
    The function returns a pointer to the created content_thread_command_t
    structure.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    @param info A string representing additional information.
    @param ... Variadic arguments for additional parameters.
    @return A pointer to the created content_thread_command_t structure.
    */
    content_thread_command_t *create_content_thread(client_t *client,
    map_t *map, char *info, ...);

    /**
    @brief Destroys a content_thread_command_t structure and frees associated
    memory.
    This function destroys a content_thread_command_t structure and frees
    associated memory.
    It takes a pointer to the content (content_thread_command_t structure).
    The function does not return any value.
    @param content A pointer to the content_thread_command_t structure.
    */
    void destroy_content_thread(content_thread_command_t *content);

    /**
    @brief Joins two queues together.
    This function joins two queues together.
    It takes a pointer to the first (first queue structure) and a pointer
    to the second (second queue structure).
    The function returns a pointer to the joined queue.
    @param first A pointer to the first queue structure.
    @param second A pointer to the second queue structure.
    @return A pointer to the joined queue.
    */
    queue_t *join_queue(queue_t *first, queue_t *second);

    /**
    @brief Destroys a queue and frees associated memory.
    This function destroys a queue and frees associated memory.
    It takes a pointer to the queue (queue structure) and a boolean
    destroy_content indicating whether to destroy the content.
    The function does not return any value.
    @param queue A pointer to the queue structure.
    @param destroy_content A boolean indicating whether to destroy the content.
    */
    queue_t *destroy_queue(queue_t *queue, bool destroy_content);

    /**
    @brief Sends a broadcast message from a client.
    This function sends a broadcast message from a client to other clients.
    It takes a pointer to the client (client structure), a string str
    representing the message,
    a pointer to the sender (sender client structure), and a string
    where representing the direction.
    The function does not return any value.
    @param client A pointer to the client structure.
    @param str A string representing the message.
    @param sender A pointer to the sender client structure.
    @param where A string representing the direction.
    */
    void send_broadcast(client_t *client, char *str, client_t *sender,
    char *where);

    /**
    @brief Removes resources from a client during incantation.
    This function removes resources from a client during incantation.
    It takes a pointer to the client (client structure) and a pointer
    to the map (map structure).
    The function does not return any value.
    @param client A pointer to the client structure.
    @param map A pointer to the map structure.
    */
    void remove_ressources_incantation(client_t *client, map_t *map);

    /**
     * @brief check if a is superior to b
     * @param a An integer representing the first number
     * @param b An integer representing the second number
     * @return int
     */
    int check_min(int a, int b);

    /**
     * @brief check basic command
     * @param cmd An array of string representing the command
     * @param server A pointer to the server structure
     * @param client A pointer to the client structure
     */
    void check_basic_command(char **cmd, server_t *server, client_t *client);

    /**
     * @brief set default ressources food (10) and stone (0)
     * @param client A pointer to the client structure
     */
    void set_client_ressources(client_t *client);

    /**
     * @brief get team members
     * @param cmd command list of string
     * @param server a pointer to the server structure
     * @param client a pointer to the client structure
     * @return int return 0 on success and 84 on failure
     */
    int check_team(char **cmd, server_t *server, client_t *client);

    /**
     * @brief check if the client is in the team
     * @param client A pointer to the client structure
     * @param server A pointer to the server structure
     * @param queue A pointer to the queue structure
     * @return queue_t* A pointer to the queue structure
     */
    queue_t *check_launch_commands_in_queue(client_t *client, queue_t *queue,
    server_t *server);

    /**
     * @brief check if the client is in the team
     * @param client A pointer to the client structure
     * @param str A string representing the team name
     * @param sender A pointer to the sender client structure
     * @param where A string representing the direction
     */
    void send_broadcast(client_t *client, char *str, client_t *sender,
    char *where);

    /**
     * @brief check if the client is in the team
     * @param msg A string representing the message
     * @param client A pointer to the client structure
     * @param pos A string representing the direction
     */
    void send_message(char *msg, client_t *client, char *pos);

    /**
     * @brief Create a code object
     *
     * @param code A string representing the code
     */
    char ***create_code(char *code);

    /**
     * @brief Get the code object
     * @param client A pointer to the client structure
     * @return char*** A pointer to the code object
     */
    char ***get_code(client_t *client);

    /**
     * @brief Destroy the code object
     * @param code A pointer to the code object
     */
    void destroy_code(char ***code);

#endif /* !SERVER_H_ */
