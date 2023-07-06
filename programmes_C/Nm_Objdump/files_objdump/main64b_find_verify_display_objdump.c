/*
** EPITECH PROJECT, 2023
** same main but in 64
** File description:
** read title
*/
#include "objdump.h"

int verify_format(Elf64_Ehdr *elf, char *path)
{
    if (strncmp((char*)elf->e_ident, ELFMAG, SELFMAG) != 0 ||
        (elf->e_type != ET_EXEC &&
    elf->e_type != ET_REL && elf->e_type != ET_DYN)) {
        fprintf(stderr, "objdump: %s: File format not recognized\n", path);
        return -1;
    }
    return 0;
}

static void display_tabs_point(unsigned int j,
    unsigned int *z,
    unsigned char *w, char *t)
{
    int x = j;

    while (x % 16 != 0) {
        if (x % 4 == 0 && x % 16) {
            putchar(' ');
        }
        putchar(' ');
        ++x;
    }
    putchar(' ');
    for (unsigned int k = *z; k < j; k++) {
        putchar(isprint(w[k]) ? t[k] : '.');
    }
    for (unsigned int k = j; k < (*z) + 16; k++) {
        putchar(' ');
    }
    *z = j;
    putchar('\n');
}

static void display_arrays(char *strtab,
    Elf64_Ehdr *elf, Elf64_Shdr *shdr, int i)
{
    unsigned char *w = (unsigned char *)((char *)elf + shdr[i].sh_offset);
    unsigned int addr = shdr[i].sh_addr;

    printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
    for (unsigned int j = 0, z = 0; j < shdr[i].sh_size; j++) {
        if (j % 16 == 0) {
            printf(" %04x ", addr);
        }
        printf("%02x", w[j]);

        if (j % 4 == 3 && j % 16 != 15) {
            printf(" ");
        }
        if (j % 16 == 15 || j == shdr[i].sh_size - 1) {
            display_tabs_point(j, &z, w, (char*)w);
            addr += 16;
        }
    }
}

void objdp64_format(void *data, char *filename)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *) data;
    if (verify_format(elf, filename) == -1) {
        return;
    }
    Elf64_Shdr *shdr = (Elf64_Shdr *)(data + elf->e_shoff);
    Elf64_Shdr *sh_strtab = &shdr[elf->e_shstrndx];
    char *strtab = (char *)(data + sh_strtab->sh_offset);
    printf("\n%s:%5cfile format\n", filename, ' ');
    printf("architecture: %s, flags 0x%08x:\n\n",
    elf->e_machine == 3 ? "i386" : "notf", elf->e_flags);
    printf("start address 0x%016x\n\n", (int) elf->e_entry);
    for (int i = 0; i < elf->e_shnum; ++i) {
        char *name = &strtab[shdr[i].sh_name];
        if (shdr[i].sh_size && strcmp(name, ".strtab") &&
            strcmp(name, ".symtab") && strcmp(name, ".shstrtab") &&
            strcmp(name, ".bss")) {
            printf("Contents of section %s:\n", name);
            display_arrays(strtab, elf, shdr, i);
        }
    }
}
