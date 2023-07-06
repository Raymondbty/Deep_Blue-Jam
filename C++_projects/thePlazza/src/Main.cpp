/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** main.cpp
*/

#include "Reception.hpp"

#include <exception>
#include <string>

using std::string;
using std::cout;
using std::cerr;
using std::stoi;
using std::stod;

static const string HELP_MSG = "USAGE\n\
\t./plazza [multiplier] [cooks] [time]\n\
DESCRIPTION\n\
\tmultiplier\tmultiplier for the cooking time of the pizzas\n\
\tcooks\t\tnumber of cooks per kitchen\n\
\ttime\t\ttime in milliseconds, used by the kitchen stock to replace \
ingredients\n";

int main(int argc, char *argv[]) {
    double multiplier = 0;
    int nb_cooks = 0;
    int time = 0;
    Reception reception;

    if (
        argc == 2 && (
            string(argv[1]) == "-h" ||
            string(argv[1]) == "--help"
        )
    ) {
        cout << HELP_MSG;
        return EXIT_SUCCESS;
    }
    if (argc != 4) {
        cerr << "[!] Invalid number of arguments.\n";
        cerr << HELP_MSG;
        return EXIT_ERROR;
    }
    try {
        multiplier = stod(argv[1]);
        nb_cooks = stoi(argv[2]);
        time = stoi(argv[3]);
    } catch (std::exception &e) {
        cerr << "[!] Invalid arguments.\n";
        cerr << HELP_MSG;
        return EXIT_ERROR;
    }
    if (multiplier <= 0 || nb_cooks <= 0 || time <= 0) {
        cerr << "[!] Arguments must be positive.\n";
        cerr << HELP_MSG;
        return EXIT_ERROR;
    }
    reception.doReception(multiplier, nb_cooks, time);
    return 0;
}
