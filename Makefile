.SILENT:
NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC =	coder.c
		dongle.c
		heap_arbiter.c
		main.c
		monitor.c
		parser.c
		simulation.c
		tools.c


#source file names to object file names using pattern substitution.
SOURCES_FILES = $(SRC)

#The OBJECT_FILES variable automatically converts
OBJECT_FILES = $(SOURCES_FILES:.c=.o)

all: $(NAME)
# # Linking object files into executable
$(NAME): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(NAME)
#COMPILATION OF SOURCE FILES
#Using %.o: %.c allows you to benefit
#from make optimization to recompile only what is necessary
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

#Avoiding conflicts and improving performance
.PHONY : all clean fclean re
