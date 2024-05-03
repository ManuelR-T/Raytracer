##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

SRC =	 $(addsuffix .cpp, 				\
			$(addprefix src/, 			\
				Scene					\
				Camera					\
				main					\
				Transformations/Transformation 	\
				Shapes/AShape 	\
			)	\
		)

OBJ = $(SRC:.cpp=.o)

NAME = raytracer

CXX = g++
CFLAGS = -W -Wall -Wextra
CPPFLAGS = -iquote./include -iquote./libs

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

debug: CFLAGS += -g3 -DDEBUG
debug: re

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
