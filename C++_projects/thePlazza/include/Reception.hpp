/*
** EPITECH PROJECT, 2023
** doRecepetion.hpp
** File description:
** MAMMA MIAA
*/
#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Kitchen.hpp"

#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>

#define EXIT_ERROR 84

class Reception {

public:
    Reception();
    ~Reception();
    bool isValidPizza(const std::string& pizza);
    bool isValidSize(const std::string& size);
    bool isValidQuantity(int quantity);
    bool isValidQuantity(const std::string& quantityStr);
    bool processPizzaOrder(const std::string& command);
    void doReception(double multiplier, int nb_cooks, int time);
    void createKitchen(int nb_cooks, Pizza pizza);
    void kitchenTask();
    std::string convertToLower(const std::string& str);

private:
    std::vector<unsigned int> _kitchen_ids;
};

#endif
