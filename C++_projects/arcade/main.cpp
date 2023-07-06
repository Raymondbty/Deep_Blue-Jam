/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-aurelien.duval
** File description:
** main
*/
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>

int main(void) {
    void *handle;
    std::string tab[3] = {"./ncurse.so", "./sfml.so", "sdl.so"};
    int i = 0;
    while (i < 3) {
        handle = dlopen(tab[i].c_str(), RTLD_LAZY);
        if (handle == NULL){
            printf("%s\n", dlerror());
            return 0;
        }
        typedef void (*hello_t)();
        hello_t func = (hello_t) dlsym(handle, "entryPoint");

        if (func == NULL){
            printf("%s\n", dlerror());
            return 0;
        } else {
            func();
        }
        dlclose(handle);
        i++;
    }
}