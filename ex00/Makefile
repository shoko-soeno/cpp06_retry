NAME = convert
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98 -pedantic
SRCS = main.cpp ScalarConverter.cpp \
		PrintScalar.cpp TypeDetector.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.PHONY: valgrind
valgrind: all
	valgrind -q --log-fd=3 --leak-check=full --error-exitcode=1 ./$(NAME)