NAME = philo

LIBFT = ./includes/libft/libft.a

CC = cc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
# CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3 

SRC = ./src/main.c ./src/parsing.c \
	./src/philo_routine_helper.c ./src/philos_routine.c \
	./src/ininting_data.c ./src/check_simulation.c
OBJ = $(SRC:.c=.o)
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $^ -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean

.SECONDARY: $(OBJ)
