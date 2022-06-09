##
## EPITECH PROJECT, 2021
## makefile
## File description:
## compile files
##

SRC	=	./src/main.c	\
		src/str_to_word_array.c	\
		src/parsing_info_lidar.c	\
		src/my_strlen.c	\
		src/strn_cat.c	\
		src/str_cat.c	\
		src/turn_right_and_left.c	\
		src/roll_back.c	\
		src/end_simulation.c	\

CC	=	gcc

CFLAGS	=	-Wall -Wextra

LDFLAGS	=	-L./lib

CPPFLAGS	=	-I./include

OBJ	=	$(SRC:.c=.o)

NAME	=	ai

all:	$(NAME)

$(NAME):	$(OBJ)
		$(MAKE) -C ./lib/my/
		$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS)

clean:
	$(MAKE) -C ./lib/my/ clean
	rm -f $(OBJ)

fclean:	clean
	$(MAKE) -C ./lib/my/ fclean
	rm -f $(NAME)

re:	fclean all

.PHONY: re fclean clean all
