/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** kitchen.cpp
*/

#include "Kitchen.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

/*LISTER TOUT LES INGREDIENTS
std::map<Ingredient, int> ingredientQuantities = pizza.getAllIngredientQuantities();

for (const auto& entry : ingredientQuantities) {
    Ingredient ingredient = entry.first;
    int quantity = entry.second;

    // CALL FOR USE OF PIZZA & INGREDIENTS
// print log debug
    std::cout << "Ingredient: " << ingredient << ", Quantity: " << quantity << std::endl;
}*/

// TODO: Add round robin check
Kitchen::Kitchen(
    unsigned int id,
    double multiplier,
    unsigned int nb_cooks,
    unsigned int time,
    string& pipepath
)
    : _id(id),
    _multiplier(multiplier),
    _time(time),
    _nb_cooks(nb_cooks),
    _nb_cook_working(0),
    _status(pipepath),
    _cook_pool(nb_cooks)
{
    cout << "[+] Kitchen " << id << " created\n";
    for (unsigned int c = 0; c < _nb_cooks; c++)
        _cook_pool_status.push_back(false);
}

void Kitchen::run()
{
    while (true) {
        checkCookStatus();
        checkCookNeedToWork();
        if (_nb_cook_working == 0 && !_start_timer) {
            _chrono = std::chrono::system_clock::now();
            _start_timer = true;
            continue;
            // TODO: Start timer for 5 seconds and stop the fork if no pizza
        }
        if (_nb_cook_working > 0 && _start_timer)
            _start_timer = false;
        if (
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - _chrono
            ).count() >= 5
        )
            stop();
    }
}

void Kitchen::stop()
{
    exit(EXIT_SUCCESS);
}

void Kitchen::refill()
{
    // Implementation for refilling ingredients
}

int Kitchen::findAvailableCook()
{
    for (unsigned int c = 0; c < _nb_cooks; c++) {
        if (_cook_pool_status[c] == false)
            return c;
    }
    return -1;
}

void Kitchen::checkCookNeedToWork()
{
    int cook_id = -1;
    Pizza pizza_to_cook;

    // printf("check pizza queue\n");
    if (_pizza_queue.empty()) {
        return;
    }

    // printf("check ingredient\n");
    for (auto& pizza : _pizza_queue) {
        if (checkIngredient(pizza)) {
            pizza_to_cook = pizza;
            break;
        }
    }

    // printf("check cook\n");
    cook_id = findAvailableCook();
    if (cook_id == -1)
        return;

    // printf("cook pizza\n");
    _cook_pool[cook_id].setPizza(_pizza_queue[0]);
    _pizza_queue.erase(_pizza_queue.begin());
    _cook_pool_status[cook_id] = true;
    _nb_cook_working++;
}

bool Kitchen::checkIngredient(Pizza& pizza)
{
    std::map<Ingredient, int> ingredientQuantities = pizza.getAllIngredientQuantities();

    for (const auto& entry : ingredientQuantities) {
        if (_ingredients[entry.first] < entry.second)
            return false;
    }
    return true;
}

void Kitchen::checkCookStatus()
{
    for (unsigned int c = 0; c < _nb_cooks; c++) {
        if (_cook_pool[c].getYield()) {
            _cook_pool[c].setYield(false);
            _cook_pool_status[c] = false;
            _nb_cook_working--;
        }
    }
}
