/*
** EPITECH PROJECT, 2023
** snake_game
** File description:
** snake
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_
#include <iostream>
#include "../Interface/IGame.hpp"
#include "../Interface/AEvents.hpp"

class snake : public Game::IGame {

        std::vector<std::unique_ptr<g::Display::AObject>> &_objs;
        int snake_row;
        int snake_col;
        int dir_row;
        int dir_col;
        int nb_snake_body;
    public:
        bool init();
        bool close();
        void create_snake();
        void create_fruits();
        void handleEvent(Game::Events::AEvents &event);
        int getnbFruit();
        void collision();
        void rmfruits();
        g::Display::AObject::coordinates getposSnake();
        g::Display::AObject::coordinates getposfruit();
        std::vector<std::unique_ptr<g::Display::AObject>> &getObject();
        void checkFruit();

};

#endif /* !NIBBLER_HPP_ */
