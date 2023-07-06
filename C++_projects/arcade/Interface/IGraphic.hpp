#pragma once

#include "AObject.hpp"
#include "AEvents.hpp"
#include "IMediator.hpp"
#include "IModule.hpp"
#include "Sound.hpp"
#include <vector>
#include <list>

namespace g = Game;

namespace Graphical
{
    class IGraphic : public Game::IMod
    {
    public:
        virtual bool CheckEvents() = 0;
        //! @brief pull events(clicks, keypresses, etc) that has been passed by Mediator
        //! @return a list of events that occured
        virtual std::vector<std::unique_ptr<g::Events::AEvents>> GetEvents() = 0;
        //! @brief True if the Circle could be drawned. False otherwise.
        //! @param objs the circle to draw
        virtual bool draw(g::Display::AObject::sfml::Circle &objs) = 0;
        //! True if the Line could be drawned. False otherwise.
        //! @param objs the line to draw
        virtual bool draw(g::Display::AObject::sfml::Line &objs) = 0;
        //! @brief True if the rectangle could be drawned. False otherwise.
        //! @param objs the rectangle to draw
        virtual bool draw(g::Display::AObject::sfml::Rectangle &objs) = 0;
        //! @brief True if the Text could be drawned. False otherwise.
        //! @param objs the text to draw
        virtual bool draw(g::Display::AObject::sfml::Text &objs) = 0;
        //! @brief True if the Sprite could be drawned. False otherwise.
        //! @param objs the sprite to draw
        virtual bool draw(g::Display::AObject::sfml::Sprite &objs) = 0;
        //! @brief objects to display gotten from the game
        virtual void draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs) = 0;
        //! @brief displays the buffeded objects
        virtual bool refresh_screen() = 0;
        //! @brief Clear the screen and reset the buffer
        virtual bool clear_screen() = 0;
        //! @brief the event loop
        virtual void event_loop() = 0;
        g::ModInfo::Type getModInfo();

    };
}
