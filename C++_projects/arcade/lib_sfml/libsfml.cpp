/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-aurelien.duval
** File description:
** libsfml
*/

#include <iostream>
#include "libsfml.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../Interface/AEvents.hpp"
#include "../Interface/AObject.hpp"

bool sfml::init()
{
     sf::RenderWindow window(sf::VideoMode(GRID_COLS * GRID_SIZE, GRID_ROWS * GRID_SIZE), "Game");
}

bool sfml::clear_screen()
{
    window.clear(sf::Color::Black);
}

bool sfml::refresh_screen()
{
    window.display();
}

bool sfml::close()
{
    window.close();
}

bool sfml::toClose()
{
    return _close;
}

std::vector<std::unique_ptr<g::Events::AEvents>> sfml::GetEvents()
{
    sf::Event Event;
    std::vector<std::unique_ptr<g::Events::AEvents>> list;
    if (! this->window.pollEvent(Event)) {
        return list;
    } else if (Event.type == sf::Event::KeyPressed) {
        auto kbEvent = std::make_unique<g::Events::KeyboardEvent>();
        kbEvent->type = g::Events::KeyboardEvent::Type::KeyPressed;
        kbEvent->key = Event.key.code;
        list.push_back(std::move(kbEvent));
    }
    return list;
}

void sfml::draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs)
{
    int i = 0;
    while (objs.size() < i) {
        if (objs[i]->obj_sfml.type == Game::Display::AObject::sfml::RECTANGLE) {
            sf::RectangleShape rectangle(sf::Vector2f(objs[i]->obj_sfml.r.width, objs[i]->obj_sfml.r.height));
            rectangle.setPosition(objs[i]->pos.x, objs[i]->pos.y);
            if (objs[i]->color == "Green")
                rectangle.setFillColor(sf::Color::Green);
            if (objs[i]->color == "Red")
                rectangle.setFillColor(sf::Color::Red);
            if (objs[i]->color == "Blue")
                rectangle.setFillColor(sf::Color::Blue);
            window.draw(rectangle);
        }
        if (objs[i]->obj_sfml.type == Game::Display::AObject::sfml::CIRCLE) {
            sf::CircleShape circle(objs[i]->obj_sfml.c.radius);
            circle.setPosition(objs[i]->pos.x, objs[i]->pos.y);
            window.draw(circle);
        }
        if (objs[i]->obj_sfml.type == Game::Display::AObject::sfml::TEXT) {
            sf::Font font;
            sf::Text text;
            font.loadFromFile(objs[i]->obj_sfml.t.path);
            text.setPosition(objs[i]->pos.x, objs[i]->pos.y);
            text.setCharacterSize(objs[i]->obj_sfml.t.FontSize);
            window.draw(text);
        }
        //if (objs[i]->getType() == Game::Display::AObject::Type::LINE) {
        //    sf::VertexArray
        //}
        if (objs[i]->obj_sfml.type == Game::Display::AObject::sfml::SPRITE) {
            sf::Texture texture;
            texture.loadFromFile(objs[i]->obj_sfml.s.path);
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition(objs[i]->pos.x, objs[i]->pos.y);
            window.draw(sprite);
        }
        i++;
    }
}
    bool sfml::CheckEvents() {}
    //! @brief pull events(clicks, keypresses, etc) that has been passed by Mediator
    //! @return a list of events that occured
    bool sfml::draw(g::Display::AObject::sfml::Circle &objs) {}
    //! True if the Line could be drawned. False otherwise.
    //! @param objs the line to draw
    bool sfml::draw(g::Display::AObject::sfml::Line &objs) {}
    //! @brief True if the rectangle could be drawned. False otherwise.
    //! @param objs the rectangle to draw
    bool sfml::draw(g::Display::AObject::sfml::Rectangle &objs) {}
    //! @brief True if the Text could be drawned. False otherwise.
    //! @param objs the text to draw
    bool sfml::draw(g::Display::AObject::sfml::Text &objs) {}
    //! @brief True if the Sprite could be drawned. False otherwise.
    //! @param objs the sprite to draw
    bool sfml::draw(g::Display::AObject::sfml::Sprite &objs) {}
    //! @brief objects to display gotten from the game
    //void sfml::draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs) {}
    //! @brief displays the buffeded objects
    void sfml::event_loop() {}
    g::ModInfo::Type sfml::getModInfo() {}

extern "C" void *entryPoint()
{
    std::cout << "entry point" << std::endl;
    return new sfml();
}