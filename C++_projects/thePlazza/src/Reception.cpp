/*
** EPITECH PROJECT, 2023
** doReception.cpp
** File description:
** MAMMA MIAAA
*/
#include "Reception.hpp"
#include "InitPizza.hpp"
#include "Kitchen.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;

Reception::Reception() {
}

Reception::~Reception() {
}

void Reception::createKitchen(int nb_cooks, Pizza pizza) {
    double multiplier = 1.0;
    unsigned int time = 0;
    string pipepath = "kitchens_status_queue.pipe";
    bool stop = false;
    for (unsigned int i = 0; !stop; ++i) {
        if (!count(_kitchen_ids.begin(), _kitchen_ids.end(), i)) {
            _kitchen_ids.push_back(i);
            stop = true;
        }
    }
    pid_t pid = fork();

    if (pid == -1) {
        cerr << "[!] Cannot create the kitchen." << endl;
        return;
    }

    if (pid == 0) {
        Kitchen kitchen(_kitchen_ids[_kitchen_ids.size() - 1], multiplier, nb_cooks, time, pipepath);
        kitchen.run();
        exit(EXIT_SUCCESS);
    }
}

void Reception::doReception(double multiplier, int nb_cooks, int) {
    string command;
    InitPizza creation_pizza;
    std::map<PizzaType, Pizza> pizza = creation_pizza.initAllPizza(multiplier);
    string pipepath = "pizza_orders_queue.pipe";

    cout << "[*] Welcome to the pizzeria!\n";
    while (true) {
        cout << "> ";
        std::getline(cin, command);
        if (cin.eof()) {
            cout << "[*] Goodbye!\n";
            break;
        }
        if (command.empty()) {
            continue;
        }
        command = convertToLower(command);
        if (command == "exit") {
            cout << "[*] Goodbye!\n";
            break;
        }
        if (command == "status") {
            cout << "must be done!\n";
            continue;
        }
        if (command == "help") {
            cout << "[*] Available commands: \n";
            cout << "  - exit: Exit the program\n";
            cout << "  - help: Show available commands\n";
            continue;
        }
        if (command == "mario") {
            cout << "IT'S A-ME, MARIOOOOOOOOOOOOOO!\n";
            continue;
        }
        /*std::vector<KitchenIPC::order_t> pizzaOrders = processPizzaOrder(command);//ICI LE KITCHEN CREATE VIA NB PIZZAS
            if (!pizzaOrders.empty()) {
                cout << "Pizza order placed successfully!\n";
                for (const auto& order : pizzaOrders) {
                    createKitchen(nb_cooks, order);
                }
            }*/
        if (processPizzaOrder(command)) {
            cout << "[+] Pizza order placed successfully!\n";
            createKitchen(nb_cooks, pizza[Margarita]);
            continue;
        }
        cout << "[!] Invalid pizza order. Please try again.\n";
    }
}
/*std::vector<KitchenIPC::order_t> Reception::processPizzaOrder(const std::string& command) { ICI UN PROCESS ORDER MAIS QUI RETURN SVECTOR SIZE QUANTITY AND TYPEPIZZA
    std::vector<KitchenIPC::order_t> orders;
    std::stringstream ss(command);
    std::string order;

    while (std::getline(ss, order, ';')) {
        std::stringstream orderStream(order);
        std::string pizza;
        std::string size;
        std::string quantityStr;

        if (
            !(orderStream >> pizza >> size >> quantityStr) ||
            !isValidPizza(pizza) ||
            !isValidSize(size) ||
            !isValidQuantity(quantityStr)
        )
        {
            std::cerr << "Invalid pizza order: " << order << std::endl;
            continue;
        }

        int quantity = std::stoi(quantityStr.substr(1));

        KitchenIPC::order_t pizzaOrder;
        pizzaOrder.pizza_type = convertToPizzaType(pizza);
        pizzaOrder.pizza_size = convertToPizzaSize(size);
        orders.push_back(pizzaOrder);

        std::cout << "Ordered: " << pizza << " (" << size << ") x" << quantity << std::endl;
    }

    return orders;
}*/
bool Reception::processPizzaOrder(const string &command) {
    stringstream ss(command);
    string order;

    while (std::getline(ss, order, ';')) {
        stringstream orderStream(order);
        string pizza;
        string size;
        string quantityStr;

        if (
            !(orderStream >> pizza >> size >> quantityStr) ||
            !isValidPizza(pizza) ||
            !isValidSize(size) ||
            !isValidQuantity(quantityStr)
        )
            return false;

        int quantity = std::stoi(quantityStr.substr(1));

        cout << "Ordered: " << pizza << " (" << size << ") x";
        cout << quantity << "\n";
    }
    return true;
}

bool Reception::isValidPizza(const string& pizza) {
    return (
        pizza == "regina" ||
        pizza == "fantasia" ||
        pizza == "margarita" ||
        pizza == "americana"
    );
}

bool Reception::isValidSize(const string& size) {
    return (
        size == "s" ||
        size == "m" ||
        size == "l" ||
        size == "xl" ||
        size == "xxl"
    );
}

bool Reception::isValidQuantity(const string& quantityStr) {
    if (quantityStr[0] == 'x' && quantityStr.size() > 1) {
        int quantity = std::stoi(quantityStr.substr(1));
        return (quantity > 0);
    }
    return false;
}

string Reception::convertToLower(const string& str) {
    string lowerStr = str;

    for (char &c : lowerStr)
        c = std::tolower(c);
    return lowerStr;
}
