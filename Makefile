##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

SRC =	 $(addsuffix .c, 				\
			$(addprefix src/, 			\
				main					\
			)	\
		)

OBJ = $(SRC:.c=.o)

NAME = raytracer

CXX = g++
CFLAGS = -W -Wall -Wextra
CPPFLAGS = -iquote./include

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)

%.o: %.c
	$(CXX) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

debug: CFLAGS += -g3 -DDEBUG
debug: re

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
