RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

CC      = cc
CFLAGS  = -g -Wall -Wextra -Werror -I. -Iincludes

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_DIR = ./minilibx-linux
	MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif

ifeq ($(UNAME_S), Darwin)
	MLX_DIR = ./mlx
	MLX     = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

LIBFT_DIR   = includes/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_LINK  = -L$(LIBFT_DIR) -lft

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
			$(SRC_DIR)/parsing/parse_config.c\
			$(SRC_DIR)/parsing/parse_config1.c\
			$(SRC_DIR)/parsing/parse_map_closed.c\
			$(SRC_DIR)/parsing/parse_map_closed1.c\
			$(SRC_DIR)/parsing/parse_map.c\
			$(SRC_DIR)/parsing/parse_map1.c\
			$(SRC_DIR)/parsing/parse_map2.c\
			$(SRC_DIR)/parsing/parse_player.c\
			$(SRC_DIR)/parsing/parse_spaces.c\
			$(SRC_DIR)/parsing/parse_validate_map.c\
			$(SRC_DIR)/parsing/parse_validate_map1.c\
			$(SRC_DIR)/parsing/parse_validate.c\
			$(SRC_DIR)/parsing/parse_validate1.c\
			$(SRC_DIR)/parsing/parse_validate2.c\
			$(SRC_DIR)/parsing/parsing_utils.c\
			$(SRC_DIR)/parsing/reading.c\
			$(SRC_DIR)/parsing/reading1.c

OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME    = cub3D

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
