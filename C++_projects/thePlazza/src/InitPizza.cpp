/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** iniPizza.cpp
*/

#include "InitPizza.hpp"

InitPizza::InitPizza()
{
}

InitPizza::~InitPizza()
{
}

Pizza InitPizza::initMargerita(int multiplier)
{
    Pizza pizza;

    pizza.setPizzaType(Margarita);
    pizza.bake_time = 1 * multiplier;
    pizza.removeIngredient(Doe, 1 * multiplier);
    pizza.removeIngredient(Tomato, 1 * multiplier);
    pizza.removeIngredient(Gruyere, 1 * multiplier);
    return pizza;
}

Pizza InitPizza::initRegina(int multiplier)
{
    Pizza pizza;

    pizza.setPizzaType(Regina);
    pizza.bake_time = 2 * multiplier;
    pizza.removeIngredient(Doe, 1 * multiplier);
    pizza.removeIngredient(Tomato, 1 * multiplier);
    pizza.removeIngredient(Gruyere, 1 * multiplier);
    pizza.removeIngredient(Ham, 1 * multiplier);
    pizza.removeIngredient(Mushrooms, 1 * multiplier);
    return pizza;
}

Pizza InitPizza::initAmericana(int multiplier)
{
    Pizza pizza;

    pizza.setPizzaType(Americana);
    pizza.bake_time = 2 * multiplier;
    pizza.removeIngredient(Doe, 1 * multiplier);
    pizza.removeIngredient(Tomato, 1 * multiplier);
    pizza.removeIngredient(Gruyere, 1 * multiplier);
    pizza.removeIngredient(Steak, 1 * multiplier);
    return pizza;
}

Pizza InitPizza::initFantasia(int multiplier)
{
    Pizza pizza;

    pizza.setPizzaType(Fantasia);
    pizza.bake_time = 4 * multiplier;
    pizza.removeIngredient(Doe, 1 * multiplier);
    pizza.removeIngredient(Tomato, 1 * multiplier);
    pizza.removeIngredient(Eggplant, 1 * multiplier);
    pizza.removeIngredient(GoatCheese, 1 * multiplier);
    pizza.removeIngredient(ChiefLove, 1 * multiplier);
    return pizza;
}

std::map<PizzaType, Pizza> InitPizza::initMinimalPizzaNeeded(double multiplier)
{
    std::map<PizzaType, Pizza> pizza;

    pizza[Margarita] = initMargerita(multiplier);
    return pizza;
}

std::map<PizzaType, Pizza> InitPizza::initAllPizza(double multiplier)
{
    std::map<PizzaType, Pizza> pizza;

    pizza[Margarita] = initMargerita(multiplier);
    pizza[Regina] = initRegina(multiplier);
    pizza[Americana] = initAmericana(multiplier);
    pizza[Fantasia] = initFantasia(multiplier);
    return pizza;
}
