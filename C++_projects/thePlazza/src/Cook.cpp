/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** cook.cpp
*/

#include "Cook.hpp"
#include "Pizza.hpp"

Cook::Cook() : _yield(false)
{
    _thread = std::thread(&Cook::cookTask, this);
}

void Cook::cookTask()
{
    std::unique_lock<std::mutex> lock(_mutex);

    while(true) {
        _cond.wait(lock, [&] {return false;});
        std::this_thread::sleep_for(std::chrono::seconds(_pizza.bake_time));
        printf("Pizza is ready\n");
        _yield = true;
        // TODO: send info pizza is ready
    }
}

void Cook::setPizza(Pizza &pizza)
{
    _pizza = pizza;
}

void Cook::setYield(bool yield)
{
    _yield = yield;
}

bool Cook::getYield() const
{
    return _yield;
}
