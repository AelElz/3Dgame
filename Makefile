# ── Colors ────────────────────────────────────────────────────────────────────
RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

# ── Compiler ──────────────────────────────────────────────────────────────────
CC      = cc -g
CFLAGS  = -Wall -Wextra -Werror -Iincludes

# ── Detect OS ─────────────────────────────────────────────────────────────────
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_DIR = ./minilibx-linux
	MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif  

ifeq ($(UNAME_S), Darwin)
	MLX_DIR = ./minilibx_mac
	MLX     = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

MLXLIB      = $(MLX_DIR)/libmlx.a

LIBFT_DIR   = includes
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_LINK  = -L$(LIBFT_DIR) -lft

# ── Sources & Objects ─────────────────────────────────────────────────────────
SRC_DIR = src
OBJ_DIR = obj

SRCS    = $(SRC_DIR)/cub3d.c

OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ── Output ────────────────────────────────────────────────────────────────────
NAME    = cub3d

# ── Rules ─────────────────────────────────────────────────────────────────────
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLXLIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT_LINK) -o $(NAME)
	@echo $(GREEN)"- Finish Compiling!"$(RESET)

$(MLXLIB):
	@$(MAKE) -C $(MLX_DIR) -j1 all 

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

# Object build rule (mirror src/ into obj/)
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
