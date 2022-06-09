##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## make
##

CC 	=	gcc

SRC	=	src/main.c \
		src/launch_game_loop.c \
		src/getfile.c	\
		src/free.c	\
		src/malloc.c	\
		src/clean_string.c	\
		src/initialize_lingo.c	\
		src/lib.c	\
		src/take_input.c	\
		src/display_clues.c	\
		src/place_interrogation.c	\
		src/my_put_nbr.c	\

OBJ    = 	$(SRC:.c=.o)

NAME	=	lingo

CFLAGS	=	-Wall -Wextra -I include

RM	=	rm

all: $(NAME)

$(NAME): $(OBJ)
	 $(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
