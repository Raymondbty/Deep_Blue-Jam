/*
** EPITECH PROJECT, 2023
** nm.h
** File description:
** nm all functions
*/
#ifndef NM_H
    #define NM_H
    #include <elf.h>
    #include <string.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <elf.h>
    #include <sys/mman.h>
    #include <errno.h>
    #include <sys/stat.h>
    #define NO_TYPE '?'

typedef struct s_flags {
    int stt;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    char type;
} t_flags;

typedef struct all_other_flags {
    uint8_t stt;
    uint32_t sh_type;
    uint64_t sh_flags;
    char type;
} all_other_flags;

typedef struct {
    uint8_t stt;
    uint32_t sh_type;
    uint64_t sh_flags;
    char type;
} SymbolTypeFlags;

typedef struct d_flags {
    unsigned char stt;
    unsigned int sh_type;
    unsigned int sh_flags;
    char type;
} d_flags;

int xaccess(char *filename);
int xopen(char *filename);
void *xmmap(int fd, char *filename, unsigned int size);
char main_flags64(Elf64_Sym *arr_sym, Elf64_Shdr *shdr);
char other_flags64(Elf64_Sym *flag_array, Elf64_Shdr *shdr);
void sort_flags_64(Elf64_Sym **symtab_cpy, int begin, int end, char *strsymtab);
void display_64results(Elf64_Shdr *symsection,
    Elf64_Sym *symtab, char *strsymtab, Elf64_Shdr *shdr);
char unknown_flags64(Elf64_Sym *flag_array);
char search_for_flags64(Elf64_Sym *flag_array, Elf64_Shdr *shdr);
void set_layout_elf64(void *data, char *filename, int argc);
char unknown_flags(Elf32_Sym *array_sim);
void sort_flags(Elf32_Sym **symtab_cpy, int start, int over, char *linesym);
void render_symbols(Elf32_Shdr *symsection,
    Elf32_Sym *flag_array, char *strsymtab, Elf32_Shdr *shdr);
char list_other_flags(Elf32_Sym *symtab, Elf32_Shdr *shdr);
int verify_elf(Elf32_Ehdr *elf, char *path);
char search_for_flags(Elf32_Sym *flag_array, Elf32_Shdr *shdr);
char get_symbol_type(Elf32_Sym *symtab, Elf32_Shdr *shdr);
void set_layout_elf32(void *data, char *filename, int argc);
void my_nm_call(char *filename, int argc);
#endif
