##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## make
##

CC	=	gcc

SRC	=	src/main.c	\
		src/error_handling.c	\
		src/generate_perfect_map.c	\
		src/generate_imperfect_map.c	\
		src/verify_surrounding.c	\
		src/clear_path.c	\
		src/print_map.c	\
		src/load_imp_maze.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	generator

all:	$(NAME)

LDFLAGS	=	-L./lib

LDLIBS	=	-lmy

CPPFLAGS	=	-iquote ./include/

CFLAGS	=	-Wall -Wextra

$(NAME):	$(OBJ)
	$(MAKE) -C ./lib/my/
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

clean:
	$(MAKE) -C ./lib/my/ clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C ./lib/my/ fclean
	rm -f $(NAME)

re:     fclean all

debug:	CFLAGS += -g

debug:	all

.PHONY: all clean fclean re debug
