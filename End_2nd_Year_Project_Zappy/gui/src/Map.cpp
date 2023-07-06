/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** map.cpp
*/

#include "../includes/Render.hpp"
#include "../includes/Network.hpp"

namespace Zappy
{
    std::vector<std::vector<BoundingBox>> reassingBoxes(int newX, int newY)
    {
        // Recreate the bounding boxes for the new map
        std::vector<std::vector<BoundingBox>> newBoxes;

        for (int i = 0; i < newX; i++) {
            std::vector<BoundingBox> lineBox;
            for (int j = 0; j < newY; j++) {
                lineBox.push_back(
                    (BoundingBox){
                        (Vector3){
                            static_cast<float>(i * CUBESIZE - newX),
                            CUBESIZE / 2.0f,
                            j * CUBESIZE - newY * CUBESIZE / 2.0f - CUBESIZE / 2.0f},
                            (Vector3){
                                static_cast<float>(i * CUBESIZE - newX + CUBESIZE),
                                CUBESIZE / 2.0f,
                                static_cast<float>(j * CUBESIZE - newY * CUBESIZE / 2.0f - CUBESIZE / 2.0f + CUBESIZE)}});
            }
            newBoxes.push_back(lineBox);
        }
        return newBoxes;
    }

    std::vector<std::vector<Tile>> reassignMap(std::vector<std::vector<Tile>> oldMap, int newX, int newY)
    {
        // Create a new map with the dimensions newX and newY and copy the oldMap's content into it
        std::vector<std::vector<Tile>> newMap;

        for (int i = 0; i < newX; i++) {
            std::vector<Tile> line;
            for (int j = 0; j < newY; j++) {
                Tile tile;
                tile.x = i;
                tile.y = j;
                tile.content = std::vector<TileContent>();
                tile.models = std::vector<Model>();
                line.push_back(tile);
            }
            newMap.push_back(line);
        }

        for (int i = 0; i < newX; i++) {
            for (int j = 0; j < newY; j++) {
                if (i < oldMap.size() && j < oldMap[i].size()) {
                    newMap[i][j] = oldMap[i][j];
                }
            }
        }

        // Update the _mapBoxes

        return newMap;
    }

    void GUI::setMapSize(int x, int y)
    {
        _map = reassignMap(_map, x, y);
        _mapBoxes = reassingBoxes(x, y);
        _mapX = x;
        _mapY = y;
    }

    void GUI::drawMap(void)
    {
        for (int i = 0; i < _mapX; i++)
            for (int j = 0; j < _mapY; j++) {
                // DrawBoundingBox(_mapBoxes[i][j], RED);
                // Use drawCubeTexture to draw the map
                // Corners
                if (i == 0 && j == 0)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, WHITE, false, true, true, false);
                if (i == 0 && j == _mapY - 1)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, WHITE, true, false, true, false);
                if (i == _mapX - 1 && j == 0)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, WHITE, false, true, false, true);
                if (i == _mapX - 1 && j == _mapY - 1)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, WHITE, true, false, false, true);
                // Sides
                if (i == 0 && j != 0 && j != _mapY - 1)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, WHITE, false, false, true, false);
                if (i == _mapX - 1 && j != 0 && j != _mapY - 1)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, WHITE, false, false, false, true);
                if (j == 0 && i != 0 && i != _mapX - 1)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, WHITE, false, true, false, false);
                if (j == _mapY - 1 && i != 0 && i != _mapX - 1)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, WHITE, true, false, false, false);
                // Center
                if (i != 0 && i != _mapX - 1 && j != 0 && j != _mapY - 1)
                    DrawCubeTexture(_top, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 1, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, 1, CUBESIZE, WHITE, false, false, false, false);
                DrawCubeWires((Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, 0, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, CUBESIZE, CUBESIZE, BLACK);
            }
        // Draw water
        for (int i = -80; i < 80; i++)
            for (int j = -80; j < 80; j++)
                    DrawCubeTexture(_water, _side, (Vector3){i * CUBESIZE - _mapX + CUBESIZE / 2.0f, -1.5, j * CUBESIZE - _mapY * CUBESIZE / 2.0f}, CUBESIZE, 1, CUBESIZE, WHITE, false, false, false, false);

        // Draw a yellow transparent cube at the selectedTile position
        if (_selectedTile.x >= 0 && _selectedTile.y >= 0)
            DrawCube((Vector3){
                _selectedTile.x * CUBESIZE - _mapX + CUBESIZE / 2.0f,
                1.5f,
                _selectedTile.y * CUBESIZE - _mapY * CUBESIZE / 2.0f},
                CUBESIZE, 0.5, CUBESIZE, (Color){255, 255, 0, 100});

        // Parse the players, draw a purple rectangle on the tiles where a player is in an Incantation
        for (auto &team : _teams) {
            for (auto &player : team.players) {
                if (player.inIncantation) {
                    Color teamColorAlpha = team.color;
                    teamColorAlpha.a = 100;
                    DrawCube((Vector3){
                        player.x * CUBESIZE - _mapX + CUBESIZE / 2.0f,
                        1.5f,
                        player.y * CUBESIZE - _mapY * CUBESIZE / 2.0f},
                        CUBESIZE / 1.5, 0.5, CUBESIZE / 1.5, teamColorAlpha);
                }
            }
        }
    }

    void GUI::setTileContent(int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        // Set the tile content with the amount of each resource specified in arguments
        // Clean the tile before
        _map[x][y].content.clear();
        _map[x][y].models.clear();

        if (x < 0 || x > _mapX || y < 0 || y > _mapY) {
            throw std::invalid_argument("Invalid position");
        }

        for (int i = 0; i < food; i++)
            _map[x][y].content.push_back(FOOD);
        for (int i = 0; i < linemate; i++)
            _map[x][y].content.push_back(LINEMATE);
        for (int i = 0; i < deraumere; i++)
            _map[x][y].content.push_back(DERAUMERE);
        for (int i = 0; i < sibur; i++)
            _map[x][y].content.push_back(SIBUR);
        for (int i = 0; i < mendiane; i++)
            _map[x][y].content.push_back(MENDIANE);
        for (int i = 0; i < phiras; i++)
            _map[x][y].content.push_back(PHIRAS);
        for (int i = 0; i < thystame; i++)
            _map[x][y].content.push_back(THYSTAME);
    }

    void GUI::removeItem(int x, int y, TileContent item)
    {
        // Remove the item from the tile
        for (int i = 0; i < _map[x][y].content.size(); i++) {
            if (_map[x][y].content[i] == item) {
                _map[x][y].content.erase(_map[x][y].content.begin() + i);
                _map[x][y].models.erase(_map[x][y].models.begin() + i);
                break;
            }
        }
    }

    void GUI::drawModels(void)
    {
        int offset = 0;
        // Parse the map, draw the items contained in each tile on the map
        for (int i = 0; i < _mapX; i++)
            for (int j = 0; j < _mapY; j++) {
                offset = 0;
                if (_map[i][j].content.size() == 0)
                    continue;
                for (int k = 0; k < _map[i][j].content.size(); k++) {
                    if (k % 4 == 0)
                        offset += 1;
                    Vector3 vectorOffset = (Vector3){(i * CUBESIZE - _mapX + 0.2f) + (k % 4 * 0.8f), // Offsets
                    1.5f,
                    (j * CUBESIZE - _mapY * CUBESIZE / 2.0f - 2.0f) + (offset * 0.8f)};
                    switch (_map[i][j].content[k]) {
                        case FOOD:
                            DrawModelEx(_models.foodModel, vectorOffset, (Vector3){0, 1, 0}, _models.rotation, _models.stoneScale, WHITE);
                            break;
                        case LINEMATE:
                            DrawModelEx(_models.linemateModel, vectorOffset, (Vector3){0, 1, 0}, _models.rotation, _models.stoneScale, WHITE);
                            break;
                        case DERAUMERE:
                            DrawModelEx(_models.deraumereModel, vectorOffset, (Vector3){0, 1, 0}, _models.rotation, _models.stoneScale, WHITE);
                            break;
                        case SIBUR:
                            DrawModelEx(_models.siburModel, vectorOffset, (Vector3){0, 1, 0}, _models.rotation, _models.stoneScale, WHITE);
                            break;
                        case MENDIANE:
                            DrawModelEx(_models.mendianeModel, vectorOffset, (Vector3){0, 1, 0}, _models.rotation, _models.stoneScale, WHITE);
                            break;
                        case PHIRAS:
                            DrawModelEx(_models.phirasModel, vectorOffset, (Vector3){0, 1, 0}, _models.rotation, _models.stoneScale, WHITE);
                            break;
                        case THYSTAME:
                            DrawModelEx(_models.thystameModel, vectorOffset, (Vector3){0, 1, 0}, _models.rotation, _models.stoneScale, WHITE);
                            break;
                    }
                }
            }
    }

    void GUI::createModelsStruct(void)
    {
        _models.rotation = 0.0f;
        _models.foodModel = createModel("assets/models/apple.obj", "assets/textures/apple.png");
        _models.linemateModel = createModel("assets/models/gems/linemate.obj", "assets/textures/PalleteTex.png");
        _models.deraumereModel = createModel("assets/models/gems/emerald.obj", "assets/textures/PalleteTex.png");
        _models.siburModel = createModel("assets/models/gems/rubis.obj", "assets/textures/PalleteTex.png");
        _models.mendianeModel = createModel("assets/models/gems/diamond.obj", "assets/textures/PalleteTex.png");
        _models.phirasModel = createModel("assets/models/gems/saphir.obj", "assets/textures/PalleteTex.png");
        _models.thystameModel = createModel("assets/models/gems/amethyst.obj", "assets/textures/PalleteTex.png");
        _models.eggModel = createModel("assets/models/egg.obj", "");

        _playerModel = createModel("assets/models/player.iqm", "");
    }

    void GUI::createSeasonTextures(void)
    {
        _seasonTextures.spring = LoadTexture("assets/textures/grass.png");
        Image side = LoadImage("assets/textures/side.png");
        ImageFlipVertical(&side);
        _seasonTextures.springSide = LoadTextureFromImage(side);
        _seasonTextures.summer = LoadTexture("assets/textures/sand.png");
        _seasonTextures.summerSide = LoadTexture("assets/textures/sand.png");
        _seasonTextures.winter = LoadTexture("assets/textures/snow.png");
        side = LoadImage("assets/textures/snowside.png");
        ImageFlipVertical(&side);
        _seasonTextures.winterSide = LoadTextureFromImage(side);
        _top = _seasonTextures.spring;
        _side = _seasonTextures.springSide;
    }

}