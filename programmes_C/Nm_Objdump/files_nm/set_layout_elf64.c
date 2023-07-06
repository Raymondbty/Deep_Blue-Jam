/*
** EPITECH PROJECT, 2023
** find_section_symtab.c
** File description:
** find sections of symbols arrays
*/
#include "nm.h"

static Elf64_Shdr *search_flags_section(Elf64_Ehdr *elf,
    Elf64_Shdr *shdrs, char *strtab)
{
    int e = 0;
    Elf64_Shdr *symboles_array_tab = NULL;
    for (e = 0; e < elf->e_shnum; e++) {
        if (strcmp(strtab + shdrs[e].sh_name, ".symtab") == 0) {
            symboles_array_tab = &shdrs[e];
        }
    }
    return (symboles_array_tab);
}

static Elf64_Shdr *search_section_line(Elf64_Ehdr *elf,
    Elf64_Shdr *shdrs, char *strtab)
{
    int e = 0;
    Elf64_Shdr *section_array = NULL;

    for (e = 0; e < elf->e_shnum; e++) {
        if (strcmp(strtab + shdrs[e].sh_name, ".strtab") == 0)
            section_array = &shdrs[e];
    }
    return (section_array);
}

static int verify_elf2(Elf64_Ehdr *elf, char *path)
{
    if (elf->e_ident[EI_MAG0] != ELFMAG0
        || elf->e_ident[EI_MAG1] != ELFMAG1
        || elf->e_ident[EI_MAG2] != ELFMAG2
        || elf->e_ident[EI_MAG3] != ELFMAG3
        || (elf->e_type != ET_EXEC && elf->e_type !=
            ET_REL && elf->e_type != ET_DYN)) {
        fprintf(stderr, "nm: %s: File format not recognized\n", path);
        return (0);
    }
    return (1);
}

void set_layout_elf64(void *data, char *filename, int argc)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr*)data;
    Elf64_Shdr *shdrs = (Elf64_Shdr*)(data + elf->e_shoff);
    char *strtab = (char*)(data + shdrs[elf->e_shstrndx].sh_offset);
    Elf64_Shdr *symtab_section = search_flags_section(elf, shdrs, strtab);
    Elf64_Shdr *strtab_section = search_section_line(elf, shdrs, strtab);

    if (!verify_elf2(elf, filename))
        return;
    if (argc > 2)
        printf("\n%s:\n", filename);
    if (symtab_section == NULL || strtab_section == NULL) {
        fprintf(stderr, "nm: %s: no symbols\n", filename);
        return;
    }
    Elf64_Sym *symtab = (Elf64_Sym*)((char*)data + symtab_section->sh_offset);
    char *strsymtab = (char*)((char*)data + strtab_section->sh_offset);
    display_64results(symtab_section, symtab, strsymtab, shdrs);
}
