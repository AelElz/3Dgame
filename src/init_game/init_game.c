/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:27:48 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/19 16:33:56 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3d");
	if (!game->win)
		return (1);
	return (0);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_down, game);
	mlx_hook(game->win, 3, 1L << 1, key_up, game);
	mlx_hook(game->win, 17, 0, win_close, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
}

void	init_player(t_game *game)
{
	game->player.pos.x = game->map.player.player_x;
	game->player.pos.y = game->map.player.player_y;
	game->player.dir.x = cos(game->map.player.angle * PI / 180.0);
	game->player.dir.y = sin(game->map.player.angle * PI / 180.0);
	cam_make_plane(&game->player, FOV_DEG);
	game->player.move_spd = 0.03;
	game->player.rot_spd = 0.02;
}

int	init_graphics(t_game *game)
{
	int	rc;

	if (init_mlx(game))
		return (printf("mlx init failed\n"), 1);
	game->map.mlx = game->mlx;
	load_textures(game);
	init_hooks(game);
	rc = img_new(game, &game->frame, WIN_W, WIN_H);
	if (rc != 0 || !game->frame.img || !game->frame.pixels)
		return (printf("frame create failed\n"), 1);
	return (0);
}

int	game_init(t_game *game, char *cub_path)
{
	int	parsed;

	ft_memset(game, 0, sizeof(*game));
	parsed = read_file(cub_path, &game->map);
	if (!parsed)
	{
		printf("Error: Failed to parse map file, exiting\n");
		return (1);
	}
	set_defaults_if_empty(game);
	if (init_graphics(game))
		return (1);
	init_player(game);
	game->running = true;
	return (0);
}
