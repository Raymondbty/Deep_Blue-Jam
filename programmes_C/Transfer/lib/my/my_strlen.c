/*
** EPITECH PROJECT, 2021
** my_strlen.c
** File description:
** counts and returns the nb of characters in the string passed as parameter
*/

int my_strlen(char const *str)
{
    int a = 0;
    while (str[a] != '\0') {
        a++;
    }
    return (a);
}
