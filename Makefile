RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

CC      = cc
CFLAGS  = -g -Wall -Wextra -Werror -I. -Iincludes

UNAME_S := $(shell uname -s)

# === MLX SETUP =====================================================

ifeq ($(UNAME_S), Linux)
	MLX     = -lmlx -lXext -lX11 -lm -lz
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
			$(SRC_DIR)/init_game/clean.c\
			$(SRC_DIR)/move/move.c\
			$(SRC_DIR)/move/move_check.c\
			$(SRC_DIR)/move/move_turn.c\
			$(SRC_DIR)/ray/ray.c\
			$(SRC_DIR)/ray/ray_cam.c\
			$(SRC_DIR)/ray/ray_tex.c\
			$(SRC_DIR)/parsing/parsin_main/parsing_main_new.c\
			$(SRC_DIR)/parsing/parsin_main/parsing_main2.c\
			$(SRC_DIR)/parsing/parsin_main/parsing_main3.c\
			$(SRC_DIR)/parsing/parsin_main/parsing_main4.c\
			$(SRC_DIR)/parsing/parsin_main/parsing_main5.c\
			$(SRC_DIR)/parsing/parsin_utils/parsing_utils1.c\
			$(SRC_DIR)/parsing/parsin_utils/parsing_utils2.c\
			$(SRC_DIR)/parsing/parsin_utils/parsing_utils3.c\
			$(SRC_DIR)/parsing/colors/parsing.colors.c\
			$(SRC_DIR)/parsing/colors/parsing.colors2.c\
			$(SRC_DIR)/parsing/maps/parsing_map1.c\
			$(SRC_DIR)/parsing/maps/parsing_map2.c\
			$(SRC_DIR)/parsing/maps/parsing_map3.c\
			$(SRC_DIR)/parsing/maps/parsing_map4.c\
			$(SRC_DIR)/parsing/maps/parsing_map5.c\
			$(SRC_DIR)/parsing/player/parcing_player.c\
			$(SRC_DIR)/parsing/textures/parsing_textures.c\
			$(SRC_DIR)/parsing/textures/parsing_textures2.c\
			$(SRC_DIR)/parsing/textures/parsing_textures3.c

OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME    = cub3D

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
