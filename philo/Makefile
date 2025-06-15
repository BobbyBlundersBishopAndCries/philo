LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard src/*.c)
HDRS = philo.h
OBJS = $(SRCS:.c=.o)
NAME = philo

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 