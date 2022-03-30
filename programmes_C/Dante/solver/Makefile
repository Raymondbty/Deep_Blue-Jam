##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## make
##

CC	=	gcc

SRC	=	src/main.c	\
		src/solve_maze.c	\
		src/create_tab_maze.c	\
		src/draw_path.c	\
		src/checker_fun.c	\
		src/check_next_pos.c

OBJ	=	$(SRC:.c=.o)

NAME	=	solver

all:	$(NAME)

LDFLAGS	=	-L./lib

LDLIBS	=	-lmy

CPPFLAGS	=	-iquote ./include/

CFLAGS	=	-Wall -Wextra

$(NAME):	$(OBJ)
	$(MAKE) -C ./lib/my/
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./lib/my/ clean

fclean: clean
	$(MAKE) -C ./lib/my/ fclean
	rm -f $(NAME)

re:     fclean all

debug:	CFLAGS += -g

debug:	all

.PHONY: all clean fclean re debug
