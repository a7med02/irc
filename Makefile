NAME = irc
SRCS = main.cpp
CC = c++
CFLAGS =  -Wall -Wextra -Werror -std=c++98
OBJ = $(SRCS:.cpp=.o)
RM = rm -f

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

