##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## makefile of project BSQ
##

CC	=	gcc

SRC	=	src/main.c	\
		src/do_h.c      \
		src/win_condition.c	\
		src/replace_storage.c   \
		src/boxes_handling.c	\
		src/error_reporter.c	\
		src/respawn.c	\
		src/error_functions.c	\
		src/keyboard.c	\
		src/left_function.c	\
		src/right_function.c	\
		src/up_function.c	\
		src/down_function.c	\
		src/check_char.c	\
		src/size_terminal.c	\
		src/open_file.c	\
		src/player_nb.c	\
		src/wall_handling.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	my_sokoban

CPPFLAGS	=	-I./include/ -lncurses

LDFLAGS		=	-L./lib

LDLIBS		=	-lmy

LIB	=	./lib/libmy.a

$(NAME):	$(LIB) $(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

all:	$(NAME)

$(LIB):
	make -C ./lib/my/

clean:
	rm -f $(OBJ)
	make clean -C ./lib/my/

fclean: clean
	rm -f $(NAME)
	make fclean -C ./lib/my

re:	fclean all

.PHONY:	$(NAME) all clean fclean
