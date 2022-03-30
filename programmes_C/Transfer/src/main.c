/*
** EPITECH PROJECT, 2019
** 107transfer
** File description:
** main
*/
#include "../includes/my.h"

int main(int argc, char **argv)
{
    transfer_t *transfer = malloc(sizeof(transfer_t));
    transfer->d = 0.000;
    transfer->e = 0;
    transfer->a = 1;
    transfer->b = 0.001;
    transfer->c = 1.001;
    
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0') {
        do_h();
    } else if (argc != 1 && argc % 2 != 0) {
        while (transfer->d < transfer->c) {
            reload(transfer);
            while (transfer->a < argc) {
                transfer->f = do_transfer(argc, argv[transfer->a], transfer->d);
                transfer->g = do_transfer(argc, argv[transfer->a + 1], transfer->d);
                if (transfer->g == 0 || error_handling(argv[transfer->a]) == -1 || error_handling(argv[transfer->a + 1]) == -1) {
                    return 84;
                }
                transfer->e = transfer->e * transfer->f / transfer->g;
                transfer->a = transfer->a + 2;
            }
            printf("%.3f -> %.5f\n", transfer->d, transfer->e);
            transfer->d = transfer->d + transfer->b;
        }
    } else {
        return 84;
    }
    return 0;
}

int error_handling(char *param)
{
    int a = 0;
    int b = 0;

    while (param[a] != '\0') {
        if ((param[a] >= '0' && param[a] <= '9') || param[a] == '*') {
            b = 1;
        } else {
            b = -1;
        }
        a = a + 1;
    }
    return b;
}
