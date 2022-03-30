##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## gcc all 101pong
##

NAME	=	106bombyx

SRC	=	src/do_h.c	\
		src/main.c	\
		src/bombyx.c	\

OBJ	=	$(SRC:.c=.o)

LDFLAGS	=	-L./lib

LDLIBS	=	-lmy

LIB	=	./lib/libmy.a

$(NAME):	$(LIB) $(OBJ)
	gcc $(OBJ) -Wall -Wextra -I includes -o $(NAME) $(LDLIBS) $(LDFLAGS) -lm

$(LIB):
	make -C ./lib/my/

clean:
	rm -f $(OBJ)
	make clean -C ./lib/my/

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
