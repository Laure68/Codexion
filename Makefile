.SILENT:
NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC =	coder.c
		dungle.c
		main.c
		monitor.c
		simulator.c

SOURCES_FILES = $(SRC)

OBJECT_FILES = $(SOURCES_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

PHONY : all clean fclean re
