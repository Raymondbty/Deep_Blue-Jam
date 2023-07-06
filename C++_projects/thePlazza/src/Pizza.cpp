/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** Pizza.cpp
*/

#include "Pizza.hpp"

Pizza::Pizza()
{
}

Pizza::~Pizza()
{
}

void Pizza::setPizzaType(PizzaType type)
{
    _type = type;
}

void Pizza::addIngredient(Ingredient ingredient, int quantity)
{
    _ingredients[ingredient] += quantity;
}

void Pizza::removeIngredient(Ingredient ingredient, int quantity)
{
    if (_ingredients.find(ingredient) != _ingredients.end()) {
        _ingredients[ingredient] -= quantity;
        if (_ingredients[ingredient] <= 0) {
            _ingredients.erase(ingredient);
        }
    }
}

int Pizza::getIngredientQuantity(Ingredient ingredient) const
{
    if (_ingredients.find(ingredient) != _ingredients.end()) {
        return _ingredients.at(ingredient);
    }
    return 0;
}

std::map<Ingredient, int> Pizza::getAllIngredientQuantities() const
{
    return _ingredients;
}
