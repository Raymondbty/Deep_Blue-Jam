##
## EPITECH PROJECT, 2022
## makefile
## File description:
## make
##

.PHONY:	all clean fclean re debug

all:
	$(MAKE) -C ./generator/
	$(MAKE) -C ./solver/

clean:
	$(MAKE) -C ./generator/ clean
	$(MAKE) -C ./solver/ clean

fclean:	clean
		$(MAKE) -C ./generator/ fclean
		$(MAKE) -C ./solver/ fclean

re:	fclean all

debug:
	$(MAKE) -C ./generator debug
	$(MAKE) -C ./solver debug
