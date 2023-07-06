/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-aurelien.duval
** File description:
** libncurse
*/

#ifndef LIBNCURSE_HPP_
#define LIBNCURSE_HPP_
#include "../Interface/IGraphic.hpp"
#include <ncurses.h>

extern "C" void entryPoint ();

class ncurse : public Graphical::IGraphic {
    int _key;
    WINDOW *_window;
    bool _close;
public:
    bool init();
    bool refresh_screen();
    bool clear_screen();
    bool close();
    bool toClose();
    std::vector<std::unique_ptr<g::Events::AEvents>> GetEvents();
    void draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs);
};
#endif /* !LIBNCURSE_HPP_ */
