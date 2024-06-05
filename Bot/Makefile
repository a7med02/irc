SRC = main.cpp bot.cpp
NAME = bot
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -lcurl
RM = rm -f
OBJ = $(SRC:.cpp=.o)

%.o: %.cpp %.hpp


all: $(NAME)

$(NAME): $(OBJ) $(SRC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all