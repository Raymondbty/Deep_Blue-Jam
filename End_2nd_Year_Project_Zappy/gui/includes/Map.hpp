/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** Map.hpp
*/

#pragma once

#include "Render.hpp"

namespace Zappy {

    enum TileContent {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
    };

    struct Tile {
        int x;
        int y;
        std::vector<TileContent> content;
        std::vector<Model> models;
    };

    struct Models {
        int  rotation;
        Vector3 stoneScale;
        Vector3 eggScale;
        Model foodModel;
        Model linemateModel;
        Model deraumereModel;
        Model siburModel;
        Model mendianeModel;
        Model phirasModel;
        Model thystameModel;
        Model eggModel;
    };

    #define SKY Color{116, 197, 232, 255}
}