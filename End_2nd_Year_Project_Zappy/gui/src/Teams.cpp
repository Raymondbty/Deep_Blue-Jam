/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** teams.cpp
*/

#include "../includes/Render.hpp"

namespace Zappy {

    void GUI::getTeams(void) {
        _teams.clear();
        sendCommand(_client, "tna\n");
    };

    void GUI::addTeam(const std::string name)
    {
        Team team;
        team.name = name;
        unsigned char r = GetRandomValue(20, 255);
        unsigned char g = GetRandomValue(20, 255);
        unsigned char b = GetRandomValue(20, 255);
        team.color = Color{r, g, b, 255};
        _teams.push_back(team);
    }

}
