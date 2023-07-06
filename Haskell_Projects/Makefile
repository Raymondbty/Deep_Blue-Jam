##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## make
##

NAME	=	wolfram

all:	$(NAME)

$(NAME):
	stack install

clean:
	stack clean

fclean: clean
	rm -f $(NAME)
	stack purge

re:	fclean all

.phony:	all clean fclean re
