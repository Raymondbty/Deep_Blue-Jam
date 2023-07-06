##
## EPITECH PROJECT, 2022
## plaza
## File description:
## Makefile
##

NAME	=	plazza

SRCPATH	=	src

OBJPATH	=	obj

SRC		=	Main.cpp			\
			Cook.cpp			\
			InitPizza.cpp		\
			Kitchen.cpp			\
			Pizza.cpp			\
			KitchenIPC.cpp		\
			Reception.cpp		\

OBJ = $(SRC:%.cpp=$(OBJPATH)/%.o)

CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -I./include

THREADFLAGS = -lpthread

CC = g++

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	@mkdir -p $(OBJPATH)
	$(CC) -o $@ -c $< $(CXXFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS) $(THREADFLAGS)

clean:
	rm -f $(OBJ) pipepath.txt
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
