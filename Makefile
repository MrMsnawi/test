SRC = main.c ft_atoi.c data_init.c routine.c philo.c parsing.c \
		time.c cleanup.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
NAME = philo
all : $(NAME)
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean :
	rm -rf $(OBJ)
fclean: clean
	rm -f $(NAME)
re : fclean all
.PHONY: clean