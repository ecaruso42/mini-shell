NAME			=	minishell

LIBFT_A			=	libft.a
LIBFT_DIR		=	libft/
LIBFT			=	$(addprefix $(LIBFT_DIR), $(LIBFT_A))

CC				=	gcc
INCLUDE			=	includes
CFLAGS			=	-Wall -Wextra -Werror -I$(INCLUDE)
RM				=	rm -f

EXECUTOR_DIR	=	src/executor
PARSING_DIR		=	src/parser
BUILTIN_DIR		=	src/builtins
SIGNAL_DIR 		=	src/signals

SRCS = 		minishell.c \
			src/parser/parser.c \
			src/parser/lexer.c \
			src/executor/exec_utils.c \
       		#$(wildcard $(SRC_DIR)/$(PARSING_DIR)/*.c) \
       		$(wildcard $(SRC_DIR)/$(EXECUTOR_DIR)/*.c) \
       		$(wildcard $(SRC_DIR)/$(BUILTIN_DIR)/*.c) \
       		$(wildcard $(SRC_DIR)/$(SIGNAL_DIR)/*.c) \

OBJS		=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -ltermcap
			@echo "\nLinked into executable \033[0;32mminishell\033[0m."

$(LIBFT):	
			@echo "Compiling libft.a"
			@$(MAKE) all -s -C $(LIBFT_DIR)

.c.o:
			@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

localclean:
			@$(RM) $(OBJS)
			@echo "Removed object files."

clean:		localclean
			@$(MAKE) clean -s -C $(LIBFT_DIR)
			@echo "Clean libft."

fclean:		localclean
			@$(MAKE) fclean -s -C $(LIBFT_DIR)
			@echo "Full clean libft."
			@$(RM) $(NAME)
			@echo "Removed executable."

re:			fclean all

.PHONY:		all clean fclean localclean re