/*
** EPITECH PROJECT, 2023
** KitchenIPC.cpp
** File description:
** KitchenIPC classes definition
*/

#include "KitchenIPC.hpp"

#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using std::cerr;
using std::string;

namespace KitchenIPC {
    KitchenStatus::KitchenStatus(string &pipepath)
        : _status_fd(mkfifo(pipepath.c_str(), PIPE_FLAGS))
    {
        if (_status_fd == -1) {
            _status_fd = open(pipepath.c_str(), O_RDONLY | O_NONBLOCK);

            if (_status_fd == -1)
                cerr << "[!] Cannot create the status pipes.\n";
        }
    }

    KitchenStatus::~KitchenStatus()
    {
        close(_status_fd);
    }

/*std::stack<KitchenIPC::status_t> KitchenStatus::getAllKitchensStatus() { LOCK GUARD TO AVOID CONCURENT ACCESS
    std::lock_guard<std::mutex> lock(_status_lock);

    std::stack<KitchenIPC::status_t> result;

    while (read(_status_fd, &status, sizeof(status_t)) > 0)
        result.push(status);

    return result;
}*/
    std::stack<status_t> &KitchenStatus::getAllKitchensStatus()
    {
        status_t status;

        while (read(_status_fd, &status, sizeof(status_t)) > 0)
            _status_stack.push(status);
        return _status_stack;
    }

    void KitchenStatus::sendStatus(status_t status)
    {
        std::lock_guard<std::mutex> lock(_status_lock);

        write(_status_fd, &status, sizeof(status_t));
    }

    PizzaOrder::PizzaOrder(string &pipepath)
        : _order_fd(mkfifo(pipepath.c_str(), PIPE_FLAGS))
    {
        if (_order_fd == -1) {
            _order_fd = open(pipepath.c_str(), O_RDONLY | O_NONBLOCK);

            if (_order_fd == -1)
                cerr << "[!] Cannot create the status pipes.\n";
        }
    }

    PizzaOrder::~PizzaOrder()
    {
        close(_order_fd);
    }

    std::stack<order_t> &PizzaOrder::getAllPizzaOrders()
    {
        order_t status;

        while (read(_order_fd, &status, sizeof(order_t)) > 0)
            _order_stack.push(status);
        return _order_stack;
    }

    void PizzaOrder::sendPizzaOrder(order_t order)
    {
        std::lock_guard<std::mutex> lock(_order_lock);

        write(_order_fd, &order, sizeof(order_t));
    }
}
