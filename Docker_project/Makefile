##
## EPITECH PROJECT, 2022
## lol
## File description:
## lol
##

CC	=	gcc

SRC	=	test.c

OBJ	=	$(SRC:.c=.o)

NAME	=	a.out

$(NAME):	 $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all:	$(NAME)

tests_run:
	make -C tests/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make fclean -C ./tests

re:	fclean all

.PHONY:	$(NAME) all clean fclean
