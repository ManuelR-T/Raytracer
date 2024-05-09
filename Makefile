##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

SRC =	 $(addsuffix .cpp, 				\
			$(addprefix src/, 			\
				$(addprefix Parsing/, 	\
					Factory				\
					ParseInformations	\
					SceneParser)		\
				$(addprefix Error/, 	\
					Exception) 			\
				Scene					\
				Camera					\
				main					\
				Transformations/Transformation 	\
				$(addprefix Shapes/, 	\
					AShape				\
					Cube				\
					Cones 	\
				)	\
			)	\
		)

OBJ = $(SRC:.cpp=.o)

NAME = raytracer

CXX = g++
CFLAGS = -W -Wall -Wextra -lconfig++
CPPFLAGS = -iquote./include -iquote./libs -std=c++20

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
