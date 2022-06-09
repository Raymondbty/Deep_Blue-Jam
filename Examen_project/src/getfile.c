/*
** EPITECH PROJECT, 2022
** getfile.c
** File description:
** getfile
*/
#include "my.h"

char *help_take_file(char *path)
{
    size_t a = 0;
    size_t b = 0;
    char **content = NULL;

    return take_file(path, a, b, content);
}

char *take_file(char *path, size_t a, size_t b, char **content)
{
    FILE *fd = fopen(path, "r");
    char *current_line = NULL;

    if (fd == NULL)
        return NULL;
    while (getdelim(&current_line, &b, '\n', fd) != -1) {
        if ((content = help_malloc_content(content)) == NULL) {
            mr_clean_tab_bis(content);
            return NULL;
        }
        if ((content[a] = strdup(&current_line[0])) == NULL) {
            mr_clean_tab_bis(content);
            return NULL;
        }
        a = a + 1;
    }
    mr_clean_tab(content);
    loop_free(current_line);
    fclose(fd);
    return free_random(content);
}
