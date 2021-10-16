SRCS = main.c philo.c syntax_checking.c threading.c tools.c utils.c

NAME = philo
cc = gcc
CFLAGS =  -Wall -Wextra -Werror
all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm philo

fclean: clean
	@echo everything been cleaned

re: fclean all

.PHONY: all clean fclean  re

