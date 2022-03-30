/*
** EPITECH PROJECT, 2021
** 104.c
** File description:
** main functions for project
*/
#include "../includes/my.h"

int exo3arg(char **argv)
{
    int n = atoi(argv[1]);//initial population
    float k = atof(argv[2]);// growth rate 1-4
    float a = n; //population

    if (n <= 0) {
        printf("n : wrong number");
        return 84;
    }
    if (k < 1 || k > 4) { 
        printf("k : Wrong growth rate\n");
        return 84;
    }
    for (int b = 1; b <= 100; b++) {
        printf("%d %.2f\n", b, a);
        a = (k * a) * (1000 - a) / 1000;
    }
    return 0;
}

int exo4arg(char **argv)
{
    int n = atoi(argv[1]);//initial population
    int k = 100;//gorwth rate
    double a = n;//population
    int i0 = atoi(argv[2]);//argc 3  = i0
    int i1 = atoi(argv[3]);//argc 4 = i1
    
    if (n <= 0) {
        printf("n : Wrong growth rate\n");
        return 84;
    }
    if (a <= 0) {
        printf("arg 3 : wrong number\n");
        return 84;
    }
    if (i1 <= 0 || i1 <= a) {
	printf("arg 4 : wrong number\n");
        return 84;
    }

    while (k <= 400) {
        a = n;
        for (int i = 1; i <= i1; i++){
            if (i >= i0)
                printf("%.2f %.2f\n", k * 0.01, a);
            a = (k * 0.01) * a * (1000 - a) / 1000;
        }
        k += 1;
    }
    return 0;
}
