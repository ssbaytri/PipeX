NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

M_SRCS = Mandatory/pipex.c
M_OBJS = $(M_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(M_OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(M_OBJS) -o $(NAME) $(LIBFT_A)

$(LIBFT_A):
	@if [ ! -f "$(LIBFT_A)" ]; then \
		echo "Building libft..."; \
		make -C $(LIBFT_DIR); \
	fi

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(M_OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
