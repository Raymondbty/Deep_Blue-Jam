/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-aurelien.duval
** File description:
** libsfml
*/

#ifndef LIBSFML_HPP_
#define LIBSFML_HPP_
#include "../Interface/IGraphic.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../Interface/IModule.hpp"

extern "C" void *entryPoint ();

class sfml : public Graphical::IGraphic {
    sf::RenderWindow window;
    bool _close;
    const int GRID_SIZE = 20;
    const int GRID_ROWS = 30;
    const int GRID_COLS = 40;
    const int NUM_FRUITS = 1;

public:
    bool init();
    bool refresh_screen();
    bool clear_screen();
    bool close();
    bool toClose();
    std::vector<std::unique_ptr<g::Events::AEvents>> GetEvents();
    void draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs);
    bool CheckEvents() override;
    //! @brief pull events(clicks, keypresses, etc) that has been passed by Mediator
    //! @return a list of events that occured
    bool draw(g::Display::AObject::sfml::Circle &objs) override;
    //! True if the Line could be drawned. False otherwise.
    //! @param objs the line to draw
    bool draw(g::Display::AObject::sfml::Line &objs) override;
    //! @brief True if the rectangle could be drawned. False otherwise.
    //! @param objs the rectangle to draw
    bool draw(g::Display::AObject::sfml::Rectangle &objs) override;
    //! @brief True if the Text could be drawned. False otherwise.
    //! @param objs the text to draw
    bool draw(g::Display::AObject::sfml::Text &objs) override;
    //! @brief True if the Sprite could be drawned. False otherwise.
    //! @param objs the sprite to draw
    bool draw(g::Display::AObject::sfml::Sprite &objs) override;
    //! @brief objects to display gotten from the game
   // void draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs) override;
    //! @brief displays the buffeded objects
    void event_loop() override;
    g::ModInfo::Type getModInfo() override;

};


#endif /* !LIBSFML_HPP_ */
