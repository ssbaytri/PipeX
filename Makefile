NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

M_SRCS = Mandatory/pipex.c
M_OBJS = $(M_SRCS:.c=.o)

# Colors
RESET  = \033[0m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
RED    = \033[31m

all: $(NAME)

$(NAME): $(M_OBJS)
	@echo "$(BLUE)🔨 Compiling libft...$(RESET)"
	@make -C libft --no-print-directory > /dev/null
	@echo "$(BLUE)🚀 Building pipex...$(RESET)"
	@$(CC) $(CFLAGS) $(M_OBJS) -o $(NAME) ./libft/libft.a
	@echo "$(GREEN)✅ pipex successfully compiled!$(RESET)"

%.o: %.c pipex.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@make clean -C libft --no-print-directory > /dev/null
	@rm -f $(M_OBJS)
	@echo "$(GREEN)✅ Object files removed.$(RESET)"

fclean: clean
	@echo "$(YELLOW)🗑️  Removing executable...$(RESET)"
	@make fclean -C libft --no-print-directory > /dev/null
	@rm -f $(NAME)
	@echo "$(GREEN)✅ Executable removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
