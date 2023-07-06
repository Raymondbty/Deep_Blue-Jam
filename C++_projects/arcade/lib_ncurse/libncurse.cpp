/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-aurelien.duval
** File description:
** libncurse
*/
#include <iostream>
#include "libncurse.hpp"
#include "../Interface/AEvents.hpp"
#include "../Interface/AObject.hpp"
#include <ncurses.h>

bool ncurse::init()
{
    initscr();
    noecho();
    _close = false;
    _window = stdscr;
    keypad(_window, TRUE);
    return true;
}

bool ncurse::clear_screen()
{
    clear();
    _key = getch();
    return true;
}

bool ncurse::refresh_screen()
{
    refresh();
    return true;
}

bool ncurse::close()
{
    if (_close == true) {
        endwin();
        return true;
    } else{
        return false;
    }
}

bool ncurse::toClose()
{
    return _close;
}

std::vector<std::unique_ptr<g::Events::AEvents>> ncurse::GetEvents()
{
    std::unique_ptr<Game::Events::KeyboardEvent> Event(new Game::Events::KeyboardEvent());
    std::vector<std::unique_ptr<Game::Events::AEvents>> list;
    Event->type = Game::Events::KeyboardEvent::Type::KeyPressed;
    Event->key = _key;
    list.push_back(std::move(Event));
    return list;
}

void ncurse::draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs)
{
    for (const auto& n : objs) {
        mvprintw(n->pos.x, n->pos.y, "%s\n", n->obj_ncurse.caractere);
    }
}

extern "C"  void entryPoint()
{
    std::cout << "entry point" << std::endl;
}
