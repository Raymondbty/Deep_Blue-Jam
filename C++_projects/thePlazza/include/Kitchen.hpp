/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Kitchen.hpp
*/
#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "KitchenIPC.hpp"
#include "Cook.hpp"

#include <vector>
#include <string>
#include <map>

#define NB_INGREDIENTS 5

class Kitchen {
public:
    Kitchen(
        unsigned int id,
        double multiplier,
        unsigned int nb_cooks,
        unsigned int time,
        std::string &pipepath
    );
    ~Kitchen() = default;

    void run();
    void stop();
    void status();
    void refill();
    void addPizza(Pizza &pizza);

private:
    int findAvailableCook();
    void checkCookNeedToWork();
    bool checkIngredient(Pizza &pizza);
    void checkCookStatus();

    unsigned int _id;
    double _multiplier;
    unsigned int _time;
    unsigned int _nb_cooks;
    unsigned int _nb_cook_working;
    bool _start_timer;
    std::chrono::system_clock::time_point _chrono;
    KitchenIPC::KitchenStatus _status;
    std::map<Ingredient, int> _ingredients;
    std::vector<Cook> _cook_pool;
    std::vector<bool> _cook_pool_status;
    std::vector<Pizza> _pizza_queue;
};
#endif
