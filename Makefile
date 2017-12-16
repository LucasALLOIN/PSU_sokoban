##
## EPITECH PROJECT, 2017
## Project my_sokoban
## File description:
## Build my_sokoban binary.
##

SRC	=	source/main.c \
		source/map_utils.c \
		source/map_parser.c \
		source/box_manag.c \
		source/place_manag.c \
		source/player.c \
		source/player_move.c \
		source/win_loose.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Werror -Wextra -W -Wall -Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized -Wunused-but-set-variable -I ./include/ -L lib/my -lmy -lncurses

NAME	=	my_sokoban

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
		make -C lib/my
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
