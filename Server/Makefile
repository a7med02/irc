NAME = IRC
CC = c++ 
FLGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp Server.cpp Client.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLGS) $(OBJ) -o $(NAME)

%.o: %.cpp Client.hpp Server.hpp
	$(CC) $(FLGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all