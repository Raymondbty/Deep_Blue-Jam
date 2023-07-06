##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## make
##

CC = gcc

CFLAGS = -W -Wall -I./files_nm

NM = my_nm

OBJDUMP = my_objdump

NM_SRCS = $(wildcard files_nm/*.c)

NM_OBJS = $(NM_SRCS:.c=.o)

OBJDUMP_SRCS = $(wildcard files_objdump/*.c)

OBJDP_OBJS = $(OBJDUMP_SRCS:.c=.o)

nm: $(NM)

objdump: $(OBJDUMP)

all: $(NM) $(OBJDUMP)

$(NM): $(NM_OBJS)
	$(CC) -o $@ $^

$(OBJDUMP): $(OBJDP_OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(NM_OBJS) $(OBJDP_OBJS)

fclean: clean
	rm -f $(NM) $(OBJDUMP)

re: fclean all

.PHONY: all clean fclean re
