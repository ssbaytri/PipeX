M_SRCS = Mandatory/pipex.c \
       Mandatory/excute.c \
       Mandatory/tokens.c \
       Mandatory/tokens2.c \
       Mandatory/parce.c

B_SRCS = Bonus/pipex_bonus.c

M_OBJS = $(M_SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(M_OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(M_OBJS) ./libft/libft.a

bonus : $(B_OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(B_OBJS) ./libft/libft.a

%.o : %.c ./Mandatory/pipex.h ./Bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C ./libft
	rm -rf $(M_OBJS) $(B_OBJS)

fclean : clean
	make fclean -C ./libft
	rm -rf $(NAME)

re : fclean all
