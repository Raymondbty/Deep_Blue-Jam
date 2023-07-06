/*
** EPITECH PROJECT, 2023
** thread.hpp
** File description:
** kitchen are dangerous
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include "Pizza.hpp"

#include <vector>
#include <queue>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class Cook {
public:
    Cook();
    ~Cook() = default;
    void setPizza(Pizza &pizza);
    void setYield(bool yield);
    bool getYield() const;

    void cookTask();
private:
    bool _yield;
    Pizza _pizza;
    std::thread _thread;
    std::mutex _mutex;
    std::condition_variable _cond;
};

#endif
