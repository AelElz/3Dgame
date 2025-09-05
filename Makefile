RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes

MLX     = -L/usr/local/lib -lmlx -lXext -lX11 -lm -lz

LIBFT_DIR   = includes
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_LINK  = -L$(LIBFT_DIR) -l:libft.a

SRCS    =	cub3d.c math.c close.c hook.c\

OBJDIR  = obj
OBJS    = $(SRCS:%.c=$(OBJDIR)/%.o)

NAME    = cub3d

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT_LINK) -o $(NAME)
	@echo $(GREEN)"- Finish Compling!"$(RESET)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)/src

clean:
	@rm -rf $(OBJDIR)
	@echo $(RED)"🧹 Objects removed"$(RESET)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)"🧹 Binary removed"$(RESET)

re: fclean all

.PHONY: all clean fclean re
