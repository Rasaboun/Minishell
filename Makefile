NAME = minishell

CC = gcc

CCFLAGS = -Wall -Wextra -Werror

INCLUDE = -lreadline

SRC = main.c ft_tcmdsize.c ft_tcmdnew.c ft_tcmdlast.c ft_tcmdadd_back.c 

all: $(NAME)

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) Libft/libft.a $(INCLUDE)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all
