#pragma once

#include "AObject.hpp"
#include "IModule.hpp"
#include "IGame.hpp"
#include "IGraphic.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <utility>

namespace Game {
    class IGame;
}

namespace Graphical {
    class IGraphic;
}

namespace Core
{
    class IMediator
    {
    public:
        virtual ~IMediator() = default;

        IMediator() = default;

        virtual void changeGame(const std::string&) = 0;

        virtual void changeGraph(const std::string&) = 0;

        virtual void exit() = 0;

        inline Game::IGame *getGame() { return game; }

        inline Graphical::IGraphic *getGraphic() { return graphics; }

    protected:
        // The game object/main menu
        Game::IGame *game{nullptr};
        // The graphics library object
        Graphical::IGraphic *graphics{nullptr};
    };
}
