/*
** EPITECH PROJECT, 2023
** set_layout_elf32.c
** File description:
** set_layout_elf32, verify typo
*/
#include "nm.h"

static Elf32_Shdr* search_tab(Elf32_Ehdr *elf, Elf32_Shdr *sections,
    int section_count, char *section_names)
{
    Elf32_Shdr *symtab_section = NULL;
    int strtab_index = -1;
    int a = 0;

    for (a = 0; a < section_count; ++a) {
        symtab_section =
    (strcmp(&section_names[sections[a].sh_name], ".symtab")
    == 0) ? &sections[a] : symtab_section;
        if (strcmp(&section_names[sections[a].sh_name], ".strtab") == 0) {
            strtab_index = a;
        }
    }
    if (strtab_index == -1) {
        return NULL;
    }
    if (symtab_section == NULL) {
        symtab_section = &sections[strtab_index];
    }
    return symtab_section;
}

int verify_elf(Elf32_Ehdr *elf, char *path)
{
    if (memcmp(elf->e_ident, ELFMAG, SELFMAG) != 0
        || (elf->e_type != ET_EXEC && elf->e_type != ET_REL
            && elf->e_type != ET_DYN)) {
        fprintf(stderr, "nm: %s: File format not recognized\n", path);
        return (-1);
    }
    return (0);
}

void set_layout_elf32(void *data, char *filename, int argc)
{
    Elf32_Ehdr *elf = (Elf32_Ehdr*)data;
    Elf32_Shdr *sections = (Elf32_Shdr*)(data + elf->e_shoff);
    char *section_names = (char*)(data + sections[elf->e_shstrndx].sh_offset);
    Elf32_Shdr *symtab_section = search_tab(elf,
        sections, elf->e_shnum, section_names);
    Elf32_Sym *symtab = (Elf32_Sym*)(data + symtab_section->sh_offset);
    char *strsymtab = (char*)(data + sections[elf->e_shstrndx].sh_offset);

    if (verify_elf(elf, filename)) return;
    if (argc > 2) printf("\n%s:\n", filename);
    if (!symtab_section || !strsymtab) {
        fprintf(stderr, "nm: %s: no symbols\n", filename);
        return;
    }
    render_symbols(symtab_section, symtab, strsymtab, sections);
}
