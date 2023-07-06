/*
** EPITECH PROJECT, 2023
** KitchenIPC.hpp
** File description:
** KitchenIPC classes
*/

#ifndef KITCHENIPC_HPP
#define KITCHENIPC_HPP

#include "Pizza.hpp"

#include <string>
#include <condition_variable>
#include <thread>
#include <stack>

#define PIPE_FLAGS 0660

namespace KitchenIPC {
    enum StatusType {
        WORKING,
        FULL,
        EMPTY,
        TERMINATED
    };

    typedef struct status_s {
        unsigned int kitchen_id;
        StatusType kitchen_status;
        unsigned int nb_cooks;
        unsigned int nb_ingredients;
    } status_t;

    typedef struct order_s {
        enum PizzaType pizza_type;
        enum PizzaSize pizza_size;
    } order_t;


    class KitchenStatus {
    public:
        KitchenStatus(std::string &pipepath);
        ~KitchenStatus();

        std::stack<status_t> &getAllKitchensStatus();
        void sendStatus(status_t status);

    private:
        int _status_fd;
        std::mutex _status_lock;
        std::stack<status_t> _status_stack;
    };

    class PizzaOrder {
    public:
        PizzaOrder(std::string &pipepath);
        ~PizzaOrder();

        void sendPizzaOrder(order_t order);
        std::stack<order_t> &getAllPizzaOrders();
    private:
        int _order_fd;
        std::mutex _order_lock;
        std::stack<order_t> _order_stack;
    };
}
#endif
