##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

SRC =	 $(addsuffix .cpp, 				\
			$(addprefix src/, 			\
				$(addprefix Parsing/, 	\
					SceneParser)		\
				Scene					\
				Camera					\
				main					\
				Transformations/Transformation 	\
			)	\
		)

OBJ = $(SRC:.cpp=.o)

NAME = raytracer

CXX = g++
CFLAGS = -W -Wall -Wextra -lconfig++
CPPFLAGS = -iquote./include -iquote./libs -iquote./src

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
