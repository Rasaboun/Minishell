# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 15:37:01 by rasaboun          #+#    #+#              #
#    Updated: 2021/10/11 21:06:35 by dkoriaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_isdigit.c ft_split.c ft_toupper.c \
ft_atoi.c ft_isprint.c ft_memset.c ft_strchr.c  ft_strncmp.c \
ft_bzero.c ft_itoa.c ft_strdup.c ft_calloc.c \
ft_putchar_fd.c ft_strjoin.c ft_strrchr.c ft_isalnum.c \
ft_putendl_fd.c ft_isalpha.c \
ft_memcmp.c ft_putnbr_fd.c  ft_strlcpy.c ft_substr.c ft_isascii.c \
ft_memcpy.c ft_putstr_fd.c ft_strlen.c ft_tolower.c

SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

all: $(NAME)

OBJ=$(SRC:.c=.o)

OBJ_BONUS=$(SRC_BONUS:.c=.o)

bonus: $(OBJ_BONUS) $(OBJ)
	ar cr $(NAME) $(OBJ) $(OBJ_BONUS)
	ranlib $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling libft..."
	@ar cr $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n\033[0mDone !"


%.o: %.c
	@printf "\033[0;33mGenerating libft objects... %-33.33s\r" $@
	@$(CC) -o $@ -c $< $(CFLAGS)


clean:
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all
