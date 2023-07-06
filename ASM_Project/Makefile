##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## make asm
##

NAME	=	libasm.so

SRC	=	src/strlen.asm	\
		src/strcmp.asm	\
		src/strncmp.asm	\
		src/strstr.asm	\
		src/strchr.asm	\
		src/strrchr.asm	\
		src/memset.asm	\
		src/memcpy.asm	\
		src/memmove.asm	\

OBJ	=	$(SRC:.asm=.o)

ASFLAGS		= -f elf64

CFLAGS		= -fPIC -shared

all: $(NAME)

$(NAME): $(OBJ)
	 ld $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.asm
	nasm $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
