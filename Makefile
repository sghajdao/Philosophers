NAME_P := philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c init.c monitor.c philo.c utile.c utile2.c

OBJECTS = $(SRC:.c=.o)

all: $(NAME_P)

$(NAME_P): $(OBJECTS)
	@echo "\033[0;32m\n\nCompiling philosophers..."
	@$(CC) -o $(NAME_P) $(OBJECTS)
	@echo "\n\033[0;32mDone."

%.o:%.c philo.h
	@printf "\033[0;33mGenerating philosophers objects... %-10.10s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -f $(OBJECTS) $(OBJECTSB)
	@echo "\n\033[0;31mDeleted.\n"	

fclean: clean
	@rm -f $(NAME_P)

re: fclean all

norm:
	norminette .