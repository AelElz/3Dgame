/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:45:22 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/11 17:59:52 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "lo3ba_3d");
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

int	game_init(t_game *game, const char *cub_path)
{
	int	rc;

	(void)cub_path;
	ft_memset(game, 0, sizeof(*game));
	set_defaults_if_empty(game);
	build_fallback_map(game);
	if (init_mlx(game))
		return (printf("mlx init failed\n"), 1);
	init_hooks(game);
	rc = img_new(game, &game->frame, WIN_W, WIN_H);
	if (rc != 0 || !game->frame.img || !game->frame.pixels)
		return (printf("frame create failed\n"), 1);
	set_player_spawn(game);
	game->running = true;
	return (0);
}
