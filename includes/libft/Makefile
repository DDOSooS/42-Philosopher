# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 19:51:41 by aghergho          #+#    #+#              #
#    Updated: 2024/06/07 16:37:51 by aghergho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME = libft.a
BONUS = bonus

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar crs

# Source files for main functions
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
      ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
      ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_strcat_char.c\
      ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c  ft_strcmp.c\
      ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strcat.c \
      ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c \
      ft_strjoin.c ft_strtrim.c ft_putnbr_fd.c ft_putchar_fd.c \
      ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c ft_striteri.c \
      ft_itoa.c ft_split.c

# Object files for main functions
OBJ = $(SRC:.c=.o)

# Source files for bonus functions
BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
            ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

# Object files for bonus functions
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# ...
# Default target
all: $(NAME)

# Build the library
$(NAME): $(OBJ)

# Build object files for main functions
$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@
	$(AR) $(NAME) $@

# Build object files for bonus functions
$(BONUS_OBJ): %.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@
	$(AR) $(NAME) $@

# Bonus target
bonus: $(BONUS_OBJ)

# Clean the object files
clean:
	rm -f $(OBJ) $(BONUS_OBJ)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus

