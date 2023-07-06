/*
** EPITECH PROJECT, 2023
** xmmap
** File description:
** #include "nm.h"
*/
#include "nm.h"

void *xmmap(int fd, char *filename, unsigned int size)
{
    struct stat sb;
    if (fstat(fd, &sb) == -1 || sb.st_size < size) {
        close(fd);
        fprintf(stderr,
    "nm: Warning: '%s' is not an ordinary file\n", filename);
        return MAP_FAILED;
    }
    void *data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        close(fd);
        fprintf(stderr, "nm: Warning: '%s' could not be memory-mapped\n",
    filename);
        return MAP_FAILED;
    }
    return data;
}
