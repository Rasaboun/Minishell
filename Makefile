NAME		=	minishell

LIBFT_DIR	=	./Libft/
LIBFT		=	$(LIBFT_DIR)/libft.a

SRCS		=	./srcs/parsing/main.c \
					./srcs/parsing/ft_tcmdsize.c \
					./srcs/parsing/ft_tcmdnew.c \
					./srcs/parsing/ft_tcmdlast.c \
					./srcs/parsing/ft_tcmdadd_back.c \
					./srcs/parsing/ft_cutcmd.c \
					./srcs/execution/exec_builtins.c \
					./srcs/execution/exec_commands.c \
					./srcs/execution/exec_commands_utils.c \
					./srcs/execution/exec_bin.c \
					./srcs/execution/redirection.c \
					./srcs/execution/redirection_utils.c \
					./srcs/builtins/echo.c \
					./srcs/builtins/export.c \
					./srcs/builtins/export_utils.c \
					./srcs/builtins/unset.c \
					./srcs/builtins/env.c \
					./srcs/builtins/cd.c \
					./srcs/builtins/pwd.c \
					./srcs/builtins/exit.c \
					./srcs/utils/env_init.c \
					./srcs/utils/env_utils.c \
					./srcs/parsing/strtok.c \
					./srcs/parsing/utils.c \
					./srcs/utils/env_utils_2.c \
					./srcs/utils/utils.c \
					./srcs/utils/signal.c \
					./srcs/utils/utils_2.c \
					./srcs/utils/utils_3.c \
					./srcs/utils/array_utils.c \
					./srcs/utils/exit.c \
					./srcs/utils/delete_redir_in_args.c \
					./srcs/utils/delete_redir_utils.c
					
OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	./includes

CC			=	gcc #-g3 -fsanitize=address

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
