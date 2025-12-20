RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

CC      = cc
CFLAGS  = -g -Wall -Wextra -Werror -I. -Iincludes

UNAME_S := $(shell uname -s)

# === MLX SETUP =====================================================

ifeq ($(UNAME_S), Linux)
	MLX_DIR = ./minilibx-linux
	MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif

ifeq ($(UNAME_S), Darwin)
	MLX_DIR = ./mlx
	MLX     = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# === LIBFT =========================================================

LIBFT_DIR   = includes/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_LINK  = -L$(LIBFT_DIR) -lft

# === SOURCES / OBJECTS =============================================

SRC_DIR = src
OBJ_DIR = obj

SRCS    =	$(SRC_DIR)/cub3d.c\
			$(SRC_DIR)/render/events.c\
			$(SRC_DIR)/render/img.c\
			$(SRC_DIR)/render/draw.c\
			$(SRC_DIR)/render/draw_helper.c\
			$(SRC_DIR)/render/draw_wall.c\
			$(SRC_DIR)/render/draw_utils.c\
			$(SRC_DIR)/init_game/init_game.c\
			$(SRC_DIR)/init_game/default_color.c\
			$(SRC_DIR)/init_game/map_build.c\
			$(SRC_DIR)/init_game/clean.c\
			$(SRC_DIR)/init_game/fallback_map.c\
			$(SRC_DIR)/move/move.c\
			$(SRC_DIR)/move/move_check.c\
			$(SRC_DIR)/move/move_turn.c\
			$(SRC_DIR)/ray/ray.c\
			$(SRC_DIR)/ray/ray_cam.c\
			$(SRC_DIR)/ray/ray_tex.c\
			$(SRC_DIR)/parsing/gnl/get_next_line.c\
			$(SRC_DIR)/parsing/gnl/get_next_line_utils.c\
			$(SRC_DIR)/parsing/main.c\
			$(SRC_DIR)/parsing/split.c\
			$(SRC_DIR)/parsing/reading.c\
			$(SRC_DIR)/parsing/parsing.c\
			$(SRC_DIR)/parsing/parsing2.c\
			$(SRC_DIR)/parsing/parsing3.c

OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME    = cub3d

# === RULES =========================================================

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT_LINK) -o $(NAME)
	@echo $(GREEN)"- Finish Compiling!"$(RESET)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean || true
	@echo $(RED)"🧹 Objects removed"$(RESET)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean || true
	@echo $(RED)"🧹 Binary removed"$(RESET)

re: fclean all

.PHONY: all clean fclean re
