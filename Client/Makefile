NAME = client
CC = g++
INCLUDE	:= ./include
CFLAGS = -g -Wall -Wextra -I $(INCLUDE)

SRC_DIR = ./src
SRC	= $(shell find $(SRC_DIR) -type f -name "*.cpp")

OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o	: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
