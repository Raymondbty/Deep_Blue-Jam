##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## make
##

CC = gcc

CFLAGS = -W -Wall -I. -pthread -lrt

PANO = panoramix

PANO_SRCS = $(wildcard *.c)

PANO_OBJS = $(PANO_SRCS:.c=.o)

all: $(PANO)

$(PANO): $(PANO_OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(PANO_OBJS)

fclean: clean
	rm -f $(PANO)

re: fclean all

.PHONY: all clean fclean re
