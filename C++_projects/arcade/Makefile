##
## EPITECH PROJECT, 2023
## B-OOP-400-PAR-4-1-arcade-aurelien.duval
## File description:
## Makefile
##

LIB_SFML = lib_sfml/libsfml.cpp

LIB_NCURSE = lib_ncurse/libncurse.cpp

LIB_SDL = lib_sdl/libsdl.cpp

CORE_CODE = core.cpp	\

ARCADE_SNAKE_GAMING = snake_game/snake.cpp	\

ARCADE_NIBBLER_GAMING = nibbler_game/nibbler.cpp	\

ARCADE_SNAKE = arcade_snake.so

ARCADE_NIBBLER = arcade_nibbler.so

NAME1 = arcade_sfml.so

NAME2 = arcade_ncurses.so

NAME3 = arcade_sdl2.so

CORE_EXEC =	arcade

OBJ_SFML = $(LIB_SFML:.cpp=.o)

OBJ_NCURSE = $(LIB_NCURSE:.cpp=.o)

OBJ_SDL = $(LIB_SDL:.cpp=.o)

OBJ_CORE =	$(CORE_CODE:.cpp=.o)

OBJ_ARCADE_NIBBLER = $(ARCADE_NIBBLER_GAMING:.cpp=.o)

OBJ_ARCADE_SNAKE = $(ARCADE_SNAKE_GAMING:.cpp=.o)

CFLAGS = -std=gnu17 -Wall -Wextra

all: $(NAME1) $(NAME2) $(NAME3) $(ARCADE_SNAKE) $(ARCADE_NIBBLER) core

$(NAME1): $(OBJ_SFML)
	@g++ -shared -o $(NAME1) $(OBJ_SFML)
	@echo -e "\e[92;5m ====Bien joué bg==== \e[0m"
	@mv $(NAME1) lib/
	@rm -rf *.o


%.o: %.cpp
	@g++ -c -fPIC -o $@ $<
	
$(NAME2): $(OBJ_NCURSE)
	@g++ -shared -o $(NAME2) $(OBJ_NCURSE)
	@echo -e "\e[92;5m ====Bien joué bg==== \e[0m"
	@mv $(NAME2) lib/
	@rm -rf *.o

$(NAME3): $(OBJ_SDL)
	@g++ -shared -o $(NAME3) $(OBJ_SDL)
	@echo -e "\e[92;5m ====Bien joué bg==== \e[0m"
	@mv $(NAME3) lib/
	@rm -rf *.o

$(ARCADE_NIBBLER): $(OBJ_ARCADE_NIBBLER)
	g++ -shared -o $(ARCADE_NIBBLER) $(OBJ_ARCADE_NIBBLER)
	mv $(ARCADE_NIBBLER) games/

$(ARCADE_SNAKE): $(OBJ_ARCADE_SNAKE)
	@g++ -shared -o $(ARCADE_SNAKE) $(OBJ_ARCADE_SNAKE)
	mv $(ARCADE_SNAKE) games/

games: $(NAME1) $(NAME2) $(NAME3)

core: 
	@g++ open_core.cpp -o $(CORE_EXEC) -ldl
	@g++ -shared -o core.so core.cpp -fPIC -lncurses

graphicals: $(ARCADE_SNAKE)

clean:
	@rm -f $(OBJ_SFML)
	@rm -f $(OBJ_NCURSE)
	@rm -f $(OBJ_SDL)
	@rm -f gcno

fclean: clean
	@rm -rf arcade
	@rm -f games/$(ARCADE_SNAKE)
	@rm -f games/$(ARCADE_NIBBLER)
	@rm -f lib/$(NAME1)
	@rm -f lib/$(NAME2)
	@rm -f lib/$(NAME3)
	@rm -f core.so
	@rm -rf arcade
	@rm -rf snake_game/*.o
	@rm -rf nibbler_game/*.o

re: fclean all

.PHONY: clean fclean re all
