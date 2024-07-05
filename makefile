NAME = philo

LIBFT = ./includes/libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3 

SRC = ./src/main.c
OBJ = $(SRC:.c=.o)
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT):
	$(MAKE) -C ./includes/libft

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./includes/libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C ./includes/libft fclean

re: fclean all

.PHONY: all re clean fclean

.SECONDARY: $(OBJ)
