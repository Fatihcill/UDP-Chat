NAME = server
CC = g++
CFLAGS = -g -Wall -Wextra -I $(INCLUDE)
INCLUDE	:= ./include

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

qt:
	$(eval INCLUDE := $(INCLUDE) -I ../PackageManager/include)
	$(eval QTFLAGS := -fPIC -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -lQt5Core -DQT_EXT=1)
	$(CC) $(SRC) $(CFLAGS) $(QTFLAGS) -o $(NAME)

.PHONY: all clean fclean re qt