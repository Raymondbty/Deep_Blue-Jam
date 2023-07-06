/*
** EPITECH PROJECT, 2023
** plaza
** File description:
** InitPizza.hpp
*/

#ifndef INITPIZZA_HPP_
#define INITPIZZA_HPP_

#include "Pizza.hpp"
#include <map>

class InitPizza {
    public:
        InitPizza();
        ~InitPizza();

        Pizza initMargerita(int multiplier);
        Pizza initRegina(int multiplier);
        Pizza initAmericana(int multiplier);
        Pizza initFantasia(int multiplier);

        std::map<PizzaType, Pizza> initMinimalPizzaNeeded(double multiplier);
        std::map<PizzaType, Pizza> initAllPizza(double multiplier);
};

#endif
