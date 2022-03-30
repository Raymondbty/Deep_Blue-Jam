##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## make lib
##

SRC	=	my_strlen.c	\
		my_putchar.c	\
		my_put_nbr.c	\
		my_putstr.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp libmy.a ../
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
