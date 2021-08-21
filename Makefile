NAME		=	minishell

LIBFT_DIR	=	./Libft/
LIBFT		=	$(LIBFT_DIR)/libft.a

SRCS		=	./srcs/parsing/main.c \
					./srcs/parsing/ft_tcmdsize.c \
					./srcs/parsing/ft_tcmdnew.c \
					./srcs/parsing/ft_tcmdlast.c \
					./srcs/parsing/ft_tcmdadd_back.c 

OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	./includes

CC			=	gcc -g3 -fsanitize=address

HEAD		=	-I./$(INCLUDES) -I./$(LIBFT_DIR)

CCFLAGS 	=	-Wall -Wextra -Werror -lreadline

LFLAGS		=	-lreadline -L ./$(LIBFT_DIR) -lft	

all: $(NAME)

$(NAME)	:	$(OBJS) $(LIBFT)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(OBJS) $(HEAD) $(CFLAGS) $(LFLAGS) -o $@
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@echo "\nDeleting objects..."
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo "\033[0m"

fclean: clean
	@echo "\nDeleting executable..."
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean all re