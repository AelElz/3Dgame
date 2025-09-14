RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_DIR = ./minilibx-linux
	MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif  

ifeq ($(UNAME_S), Darwin)
	MLX_DIR = minilibx_mac
	MLX     = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

MLXLIB      = $(MLX_DIR)/libmlx.a

LIBFT_DIR   = includes
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_LINK  = -L$(LIBFT_DIR) -lft

SRCS    = cub3d.c

OBJDIR  = obj
OBJS    = $(SRCS:%.c=$(OBJDIR)/%.o)

NAME    = cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT_LINK) -o $(NAME)
	@echo $(GREEN)"- Finish Compiling!"$(RESET)

$(MLXLIB):
	$(MAKE) -C $(MLX_DIR) -j1 all 

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)
	@echo $(RED)"🧹 Objects removed"$(RESET)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)"🧹 Binary removed"$(RESET)

re: fclean all

.PHONY: all clean fclean re
