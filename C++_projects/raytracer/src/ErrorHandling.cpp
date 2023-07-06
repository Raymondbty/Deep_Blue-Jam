/*
** EPITECH PROJECT, 2023
** ErrorHandling.cpp
** File description:
** ErrorHandling
*/

#include "ErrorHandling.hpp"

ErrorHandling::ErrorHandling(int const ac, char const **av)
{
    if (ac == 2 && av[1] == std::string("--help"))
        showHelp(0);
    else if (ac != 2)
        showHelp(84);
    setReturnValue(0);
}

ErrorHandling::~ErrorHandling()
{
}

void ErrorHandling::setReturnValue(int value)
{
    _returnValue = value;
}

int ErrorHandling::getReturnValue()
{
    return _returnValue;
}

void ErrorHandling::showHelp(int retVal)
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
    std::exit(retVal);
}
