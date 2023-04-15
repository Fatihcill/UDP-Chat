NAME = pack
CC = g++
CFLAGS = -Wall -Wextra -I $(INCLUDE)
QTFLAGS = -fPIC -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -lQt5Core
INCLUDE	:= ./include

SRC_DIR = ./src
SRC	= $(shell find $(SRC_DIR) -type f -name "*.cpp")

OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(QTFLAGS)

%.o	: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(QTFLAGS)

all: $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re