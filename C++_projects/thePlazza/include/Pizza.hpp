/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** IPizza.hpp
*/

#ifndef IPIZZA_HPP_
#define IPIZZA_HPP_

#include "PizzaInfo.hpp"
#include <iostream>
#include <map>
#include <string>

enum Ingredient {
    Doe,
    Tomato,
    Gruyere,
    Ham,
    Mushrooms,
    Steak,
    Eggplant,
    GoatCheese,
    ChiefLove
};

class Pizza {
public:
    Pizza();
    ~Pizza();

    void setPizzaType(PizzaType type);
    void addIngredient(Ingredient ingredient, int quantity);
    void removeIngredient(Ingredient ingredient, int quantity);
    int getIngredientQuantity(Ingredient ingredient) const;
    std::map<Ingredient, int> getAllIngredientQuantities() const;

    int bake_time;
private:
    PizzaType _type;
    std::map<Ingredient, int> _ingredients;
};

#endif
