#pragma once

#include <vector>
#include "AObject.hpp"
#include "AEvents.hpp"
#include "IMediator.hpp"
#include "IModule.hpp"
#include "Sound.hpp"

namespace Game
{
    // this is used my the mediator
    class IGame : public Game::IMod
    {
        public:
            enum class GameState {
                PLAYING,
                GAMEOVER
            };

            //! @brief Virtual destructor
            ~IGame() override = default;

            //! @brief Return a list of objects to display.
            //! @return The list of objects
            virtual std::vector<std::unique_ptr<Display::AObject>> &getObject() = 0;

            //! @brief Handle one event (A key press, a click, a close event...)
            //! @param event The event to handle.
            virtual void handleEvent(Events::AEvents &event) = 0;

            //! @brief Get the score (used for saving/displaying)
            inline unsigned long getScore() { return score; }

            virtual bool UpdateFrame() {
                return true;
            }

        protected:
            GameState state{GameState::PLAYING};
            size_t score;
    };
}
