/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** Player.hpp
*/

#pragma once

#include "Render.hpp"
#include "Map.hpp"

namespace Zappy {

    struct Player {
        int id;
        float x;
        float y;
        int level;
        int direction;
        bool inIncantation;
        std::string teamName;
        std::vector<TileContent> inventory;
        std::string playerName;
    };

    struct Team {
        std::string name;
        Color color;
        std::vector<Player> players;
        std::vector<Player> egg_id;
    };

    struct Egg {
        int id;
        int x;
        int y;
        int player_id;
        Team *team;
    };
}
