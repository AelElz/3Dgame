RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

CC      = cc -g
CFLAGS  = -Wall -Wextra -Werror -Iincludes

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_DIR = ./minilibx-linux
	MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif  

ifeq ($(UNAME_S), Darwin)
	MLX_DIR = ./mlx
	MLX     = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

MLXLIB      = $(MLX_DIR)/libmlx.a

LIBFT_DIR   = includes
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_LINK  = -L$(LIBFT_DIR) -lft

SRC_DIR = src
OBJ_DIR = obj

SRCS    =	$(SRC_DIR)/cub3d.c\
			$(SRC_DIR)/game_init.c\
			$(SRC_DIR)/events.c\
			$(SRC_DIR)/move.c\
			$(SRC_DIR)/draw.c\
			$(SRC_DIR)/ray.c\
			$(SRC_DIR)/img.c

OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME    = cub3d

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLXLIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT_LINK) -o $(NAME)
	@echo $(GREEN)"- Finish Compiling!"$(RESET)

$(MLXLIB):
	@$(MAKE) -C $(MLX_DIR) -j1 all 

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo $(RED)"🧹 Objects removed"$(RESET)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)"🧹 Binary removed"$(RESET)

re: fclean all

.PHONY: all clean fclean re
