NAME = philo

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

SOURCES = main.c atoi_philo.c utils.c philo_init.c threads_routine.c
OBJECTS = $(SOURCES:.c=.o)

INCLUDE = -I inc

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(INC) $(OBJECTS) -o $(NAME)
	@echo "$(NAME) created"

clean:
	@$(RM) $(OBJECTS)
	@echo "Objects removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

run: all clean

.PHONY: all clean fclean re run
