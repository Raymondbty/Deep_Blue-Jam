##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## make 205
##


NAME    =       205IQ

SRC     =	math.c	\

CPPFLAGS  =	-Wall -Wextra -lm

.PHONY: all $(NAME) clean

all:    $(NAME)

$(NAME):        $(OBJ)
	gcc -o $(NAME) $(SRC) -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all
