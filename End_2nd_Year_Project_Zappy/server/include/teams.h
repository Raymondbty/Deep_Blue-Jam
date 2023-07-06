/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** teams.h
*/

#ifndef ZAPPIE_TEAMS_H
    #define ZAPPIE_TEAMS_H

    #define AI "AI"
    #define GUI "GUI"

    typedef struct team_s {
        char *name;
        int nb_unused_slots;
        int nb_clients;
        int max_clients;
        int *clients;
        int nbr_eggs;
    } team_t;

    void destroy_all_teams(team_t **teams);

#endif
