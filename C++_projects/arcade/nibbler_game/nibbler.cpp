/*
** EPITECH PROJECT, 2023
** snake_game
** File description:
** snake
*/
#include "nibbler.hpp"
#include "../Interface/AObject.hpp"
const int GRID_SIZE = 20;
const int GRID_ROWS = 30;
const int GRID_COLS = 40;
const int NUM_FRUITS = 1;
bool isFastMode = false;
bool isPaused = false;


bool snake::init()
{
    snake_row = GRID_ROWS / 2;
    snake_col = GRID_COLS / 2;
    dir_row = 0;
    dir_col = 1;
    nb_snake_body = 3;
    create_snake();
    create_fruits();
    return true;
}

bool snake::close()
{
    auto it = _objs.begin();
    while (it != _objs.end()) {
            it = _objs.erase(it);
    }
    return true;
}

void snake::handleEvent(Game::Events::AEvents &event)
{
    collision();
    checkFruit();
    Game::Events::KeyboardEvent &e = dynamic_cast<Game::Events::KeyboardEvent  &>(event);
    if (e.type == g::Events::KeyboardEvent::Type::KeyPressed) {
        switch (e.key) {
            default:
        case g::Events::KeyboardEvent::LEFT_ARROW :
            dir_row = 0;
            dir_col = -1;
            break;
        case g::Events::KeyboardEvent::RIGHT_ARROW:
            dir_row = 0;
            dir_col = 1;
            break;
        case g::Events::KeyboardEvent::UP_ARROW:
            dir_row = -1;
            dir_col = 0;
            break;
        case g::Events::KeyboardEvent::DOWN_ARROW:
            dir_row = 1;
            dir_col = 0;
            break;
        }
    }
    snake_row += dir_row;
    snake_col += dir_col;
    if (snake_row < 0)
        snake_row = GRID_ROWS - 1;
    if (snake_row >= GRID_ROWS)
        snake_row = 0;
    if (snake_col < 0)
        snake_col = GRID_COLS - 1;
    if (snake_col >= GRID_COLS)
        snake_col = 0;
    int nb = 0;
    for (int i = 0; i < _objs.size(); i++) {
        if (_objs[i]->name == "snake_head") {
            _objs[i]->pos = {snake_col * GRID_SIZE, snake_row * GRID_SIZE};
        }
        if (_objs[i]->name == "snake_body") {
            _objs[i]->pos = {(snake_col - nb) * GRID_SIZE, snake_row * GRID_SIZE};
            nb = nb + 1;
        }
    }
}

void snake::create_snake()
{
    std::unique_ptr<Game::Display::AObject> obj(new Game::Display::AObject());
    obj->name = "snake_head"; 
    obj->obj_sfml.type = g::Display::AObject::sfml::Type::RECTANGLE;
    obj->obj_sfml.r.height = GRID_SIZE;
    obj->obj_sfml.r.width = GRID_SIZE;
    obj->color = "Blue";
    obj->obj_ncurse.caractere = "s";
    obj->pos = {snake_col * GRID_SIZE, snake_row * GRID_SIZE};
    _objs.push_back(std::move(obj));
    for (int i = 0; i < 3; i++) {
        std::unique_ptr<Game::Display::AObject> obj(new Game::Display::AObject());
        obj->name = "snake_body"; 
        obj->obj_sfml.type = g::Display::AObject::sfml::Type::RECTANGLE;
        obj->obj_sfml.r.height = GRID_SIZE;
        obj->obj_sfml.r.width = GRID_SIZE;
        obj->color = "Green";
        obj->obj_ncurse.caractere = "o";
        obj->pos = {(snake_col - i) * GRID_SIZE, snake_row * GRID_SIZE};
        _objs.push_back(std::move(obj));
    }
}

void snake::create_fruits()
{
    std::unique_ptr<Game::Display::AObject> obj(new Game::Display::AObject());
    obj->name = "fruit"; 
    obj->obj_sfml.type = g::Display::AObject::sfml::Type::RECTANGLE;
    obj->obj_sfml.r.height = GRID_SIZE;
    obj->obj_sfml.r.width = GRID_SIZE;
    obj->color = "Red";
    obj->obj_ncurse.caractere = "x";
    obj->pos = {(rand() % GRID_COLS) * GRID_SIZE, (rand() % GRID_ROWS) * GRID_SIZE};
    _objs.push_back(std::move(obj));
}

int snake::getnbFruit()
{
    int nb = 0;
    for (int i = 0; i < _objs.size(); i++) {
        if (_objs[i]->name == "fruit") {
            nb = nb + 1;
        }
    }
    return nb;
}

g::Display::AObject::coordinates snake::getposSnake()
{
    g::Display::AObject::coordinates p;
    for (int i = 0; i < _objs.size(); i++) {
        if (_objs[i]->name == "snake_head") {
            p = _objs[i]->pos;
        }
    }
    return p;
}

g::Display::AObject::coordinates snake::getposfruit()
{
    g::Display::AObject::coordinates p;
    for (int i = 0; i < _objs.size(); i++) {
        if (_objs[i]->name == "fruit") {
            p = _objs[i]->pos;
        }
    }
    return p;
}

void snake::rmfruits()
{
    auto it = _objs.begin();
    while (it != _objs.end()) {
        if ((*it)->name == "fruit") {
            it = _objs.erase(it);
        } else {
            ++it;
        }
    }
}

void snake::collision()
{
    for (int i = 0; i < _objs.size(); i++) {
        if (getposfruit().x == getposSnake().x && getposfruit().y == getposSnake().y) {
            rmfruits();
            std::unique_ptr<Game::Display::AObject> obj(new Game::Display::AObject());
            obj->name = "snake_body"; 
            obj->obj_sfml.type = g::Display::AObject::sfml::Type::RECTANGLE;
            obj->obj_sfml.r.height = GRID_SIZE;
            obj->obj_sfml.r.width = GRID_SIZE;
            obj->color = "Green";
            obj->obj_ncurse.caractere = "o";
            obj->pos = {(snake_col - nb_snake_body) * GRID_SIZE, snake_row * GRID_SIZE};
            _objs.push_back(std::move(obj));
            nb_snake_body = nb_snake_body + 1;
        }
    }

}

void snake::checkFruit()
{
    if (getnbFruit() < 1) {
        std::unique_ptr<Game::Display::AObject> obj(new Game::Display::AObject());
        obj->name = "fruit"; 
        obj->obj_sfml.type = g::Display::AObject::sfml::Type::RECTANGLE;
        obj->obj_sfml.r.height = GRID_SIZE;
        obj->obj_sfml.r.width = GRID_SIZE;
        obj->color = "Red";
        obj->obj_ncurse.caractere = "x";
        obj->pos = {(rand() % GRID_COLS) * GRID_SIZE, (rand() % GRID_ROWS) * GRID_SIZE};
        _objs.push_back(std::move(obj));  
    }
}

std::vector<std::unique_ptr<g::Display::AObject>> &snake::getObject()
{
    return _objs;
}