/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main for GUI
*/
#include <iostream>
#include <string>
#include <cstdlib>

void printHelp() {
    std::cout << "USAGE: ./zappy_ai -p port -h machine" << std::endl;
    std::cout << "       port is the port number" << std::endl;
    std::cout << "       machine is the name of the machine; localhost by default" << std::endl;
}
/*
bool validateOptions(const std::string& option, const std::string& value) {

    if (option == "-p" || option == "-h") {
        if (value.empty()) {
            std::cerr << "Error: " << option << " option requires a value." << std::endl;
            return false;
        }
    } else if (option == "-help") {
        printHelp();
        return false;
    } else {
        std::cerr << "Error: Unknown option '" << option << "'." << std::endl;
        return false;
    }

    return true;
}

bool portVerification(const std::string& port) {

    if (port.empty()) {
        std::cerr << "Error: Port number is required. Please use the -p option." << std::endl;
        return false;
    }
    return true;
}

bool parseCommandLineArguments(int argc, char**$ argv[], std::string& port, std::string& machine) {

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-p" || arg == "-h") {
            if (i + 1 < argc) {
                std::string value = argv[i + 1];
                if (!validateOptions(arg, value)) {
                    return false;
                }

                if (arg == "-p") {
                    port = value;
                } else if (arg == "-h") {
                    machine = value;
                }
                i++;
            } else {
                std::cerr << "Error: " << arg << " option requires a value." << std::endl;
                return false;
            }
        } else if (arg == "-help") {
            printHelp();
            return false;
        } else {
            std::cerr << "Error: Unknown option '" << arg << "'." << std::endl;
            return false;
        }
    }
    return portVerification(port);
}*/

int main(int argc, char* argv[]) {

    std::string port;
    std::string machine = "localhost";

    if (!parseCommandLineArguments(argc, argv, port, machine)) {
        return 0;
    } else {
        return 84;
    }
    //next boys
    return 0;
}
