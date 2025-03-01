NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

M_SRCS = Mandatory/pipex.c

M_OBJS = $(M_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(M_OBJS)
	$(CC) $(CFLAGS) $(M_OBJS) -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(M_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re