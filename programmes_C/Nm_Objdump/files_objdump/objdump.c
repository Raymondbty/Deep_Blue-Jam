/*
** EPITECH PROJECT, 2023
** objdump.c
** File description:
** main call
*/
#include "objdump.h"

void *mmap_file(char *filename, size_t *size)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return NULL;
    }
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return NULL;
    }
    void *data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return NULL;
    }
    *size = st.st_size;
    close(fd);
    return data;
}

void my_objdump(char *filename)
{
    size_t size;
    void *data = mmap_file(filename, &size);
    if (data == NULL) {
        return;
    }
    Elf64_Ehdr *elf = (Elf64_Ehdr*) data;
    if (elf->e_ident[EI_CLASS] == ELFCLASS32) {
        call_for_32display(data, filename);
    } else if (elf->e_ident[EI_CLASS] == ELFCLASS64) {
        objdp64_format(data, filename);
    } else {
        fprintf(stderr,
                "error: unsupported ELF format in file '%s'\n", filename);
    }
    if (munmap(data, size) == -1) {
        perror("munmap");
    }
}

int main(int argc, char **argv)
{
    int a = 0;

    if (argc > 1) {
        for (a = 1; a < argc; a++) {
            my_objdump(argv[a]);
        }
    } else {
        my_objdump("./a.out");
    }
    return (0);
}
