NAME = irc
SRCS = main.cpp Server.cpp Client.cpp
CC = c++
CFLAGS =  -Wall -Wextra -Werror -std=c++98
OBJ = $(SRCS:.cpp=.o)
RM = rm -f

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp Server.hpp Client.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
