##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## nibbler
##

SRC	=	libsdl.cpp	\

OBJ	=	$(SRC:.cpp=.o)

CFLAGS	=	-std=gnu17 -Wall -Wextra

NAME	=	arcade

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ $(SRC) -o $(NAME) -I include -L lib -L /usr/lib/mingw32 -lSDL2main -lSDL2 -lstdc++
	echo -e "\e[92;5m	====Bien joué bg====	\e[0m"

clean:
	rm -f $(OBJ)
	rm -f *gcno

fclean: clean
	rm -f $(NAME)
	rm -f *~
	rm -f *.o
	rm -rf vgcore.*

re:	fclean all

.PHONY: clean fclean re all
