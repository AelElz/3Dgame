CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3 

# LIBFT       = ../../includes
# LIBFT       = $(LIBFT_DIR)/libft.a
# LIBFT_LINK  = -L$(LIBFT_DIR) -lft
SRCS    =	gnl/get_next_line.c\
			gnl/get_next_line_utils.c\
			main.c\
			split.c\
			reading.c\
			parsing.c\
			parsing2.c\
			parsing3.c

OBJS    = $(SRCS:%.c=%.o)

NAME    = cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


san: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) -o $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
