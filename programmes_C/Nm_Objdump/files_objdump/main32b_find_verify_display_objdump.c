/*
** EPITECH PROJECT, 2023
** main32b_find_verify_display_objdump.c
** File description:
** read name
*/
#include "objdump.h"

static void display_section(char *strtab, Elf32_Ehdr *elf,
                            Elf32_Shdr *shdr, int i)
{
    unsigned char *w = (unsigned char*)((char*)elf + shdr[i].sh_offset);
    int addr = shdr[i].sh_addr;
    char ascii_buffer[17] = {0};
    unsigned int j, k = 0;

    printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
    for (j = 0; j < shdr[i].sh_size; ++j, ++w) {
        printf("%s%02x%s", (j % 16 == 0) ? " " : "", *w,
    (j % 4 == 3 && j % 16 != 15) ? " " : "");
        ascii_buffer[j % 16] = isprint(*w) ? *w : '.';
        if (j % 16 == 15) {
            printf("  %s\n", ascii_buffer);
            memset(ascii_buffer, 0, sizeof(ascii_buffer));
        }
        addr += (j % 16 == 15);
    } if (shdr[i].sh_size % 16 != 0) {
        for (k = shdr[i].sh_size % 16; k < 16; ++k)
            printf("   ");
        printf("  %s\n", ascii_buffer);
    }
}

static void result_array(char *strtab, Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
    int a = 0;

    for (a = 0; a < elf->e_shnum; a++) {
        const char* name = &strtab[shdr[a].sh_name];
        if (shdr[a].sh_size != 0 && strncmp(name, ".", 1) != 0
            && strcmp(name, ".bss") != 0) {
            display_section(strtab, elf, shdr, a);
        }
    }
}

int is_valid_elf_file(Elf32_Ehdr *elf_header)
{
    if (elf_header->e_ident[EI_MAG0] != ELFMAG0
        || elf_header->e_ident[EI_MAG1] != ELFMAG1
        || elf_header->e_ident[EI_MAG2] != ELFMAG2
        || elf_header->e_ident[EI_MAG3] != ELFMAG3
        || (elf_header->e_type != ET_EXEC && elf_header->e_type
            != ET_REL && elf_header->e_type != ET_DYN)) {
        return (0);
    }
    return (1);
}

int result_array32(Elf32_Shdr *section_header, char *section_name_table)
{
    return (section_header->sh_size
            && strcmp(&section_name_table[section_header->sh_name], ".strtab")
            && strcmp(&section_name_table[section_header->sh_name], ".symtab")
            && strcmp(&section_name_table[section_header->sh_name], ".shstrtab")
            && strcmp(&section_name_table[section_header->sh_name], ".bss"));
}

void call_for_32display(void *data, char *filename)
{
    Elf32_Ehdr *elf_header = (Elf32_Ehdr*) data;
    Elf32_Shdr *section_headers = (Elf32_Shdr*) (data + elf_header->e_shoff);
    char *section_name_table = (char*)
        (data + section_headers[elf_header->e_shstrndx].sh_offset);
    size_t sz = 0;

    if (!is_valid_elf_file(elf_header)) {
        fprintf(stderr, "nm: %s: File format not recognized\n", filename);
        return;
    }
    printf("\n%s:%5cfile format\n", filename, ' ');
    printf("architecture: %s, flags 0x%08x:\n\n",
    elf_header->e_machine == 3 ? "i386" : "notf", elf_header->e_flags);
    printf("start address 0x%08x\n\n", elf_header->e_entry);
    for (sz = 0; sz < elf_header->e_shnum; ++sz) {
        if (result_array32(&section_headers[sz], section_name_table)) {
            result_array(&section_name_table[section_headers[sz].sh_name],
    elf_header, &section_headers[sz]);
        }
    }
}
