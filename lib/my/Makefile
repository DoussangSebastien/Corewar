##
## EPITECH PROJECT, 2024
## task01 day10
## File description:
## Makefile
##

SRC = $(shell find *.c)

OBJ = $(SRC:.c=.o)

NAME = libmy.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
