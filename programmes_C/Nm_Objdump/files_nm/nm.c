/*
** EPITECH PROJECT, 2023
** nm.c
** File description:
** main nm.c
*/
#include "nm.h"

int main(int argc, char **argv)
{
    int i = 1;

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            my_nm_call(argv[i], argc);
        }
    } else {
        my_nm_call("./a.out", argc);
    }
    return (1);
}

void my_nm_call(char *filename, int argc)
{
    int fd = xopen(filename);
    void *data = xmmap(fd, filename, lseek(fd, 0, SEEK_END));

    if (fd == -1 || xaccess(filename) == -1 || data == MAP_FAILED) {
        close(fd);
        return;
    }
    if (((Elf32_Ehdr*)data)->e_ident[EI_CLASS] == ELFCLASS32) {
        set_layout_elf32(data, filename, argc);
    } else {
        set_layout_elf64((Elf64_Ehdr*)data, filename, argc);
    }
    munmap(data, lseek(fd, 0, SEEK_END));
    close(fd);
}
