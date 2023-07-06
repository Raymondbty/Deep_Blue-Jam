/*
** EPITECH PROJECT, 2023
** include objdump files
** File description:
** read
*/
#ifndef _OBJDUMP_H_
    #define _OBJDUMP_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/mman.h>
    #include <errno.h>
    #include <elf.h>
    #include <sys/stat.h>
    #include <ctype.h>

void call_for_32display(void *data, char *filename);
void objdp64_format(void *data, char *filename);
void my_objdump(char *filename);
void *mmap_file(char *filename, size_t *size);
int display_array32(Elf32_Shdr* section_header, char* section_name_table);
int is_valid_elf_file(Elf32_Ehdr* elf_header);
#endif
