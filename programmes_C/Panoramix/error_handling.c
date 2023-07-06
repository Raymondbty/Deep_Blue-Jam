/*
** EPITECH PROJECT, 2023
** error_handling.c
** File description:
** lol
*/
#include "pano.h"

int validate_arguments(int argc, char **argv)
{
    if (argc == 1) {
        printf("USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights>");
        printf("<nb_refills>\n");
        return 1;
    } else if (argc != 5) {
        printf("Wrong number of arguments\n");
        return 84;
    }

    for (int i = 1; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (!isdigit(argv[i][j])) {
                printf("Invalid argument, not a number: %s\n", argv[i]);
                return 84;
            }
        }
    }

    return 0;
}

pthread_mutex_t mutex; // Mutex variable

void initializeMutex() {
    if (pthread_mutex_init(&mutex, NULL) != 0) {
    }
}

void useMutex() {
    if (pthread_mutex_lock(&mutex) != 0) {
    }


    if (pthread_mutex_unlock(&mutex) != 0) {
    }
}

void cleanupMutex() {
    if (pthread_mutex_destroy(&mutex) != 0) {
    }
}


int error_handling(int argc, char **argv)
{
    initializeMutex();
    int ret = validate_arguments(argc, argv);
    if (ret != 0) {
        return ret;
    }
    ret = parse_arguments(argv);
    if (ret != 0) {
        return ret;
    }
    cleanupMutex();
    return 0;
}
