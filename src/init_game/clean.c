/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:45:58 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 21:46:06 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_free(t_game *game)
{
	int	i;

	img_free(game, &game->tex.no);
	img_free(game, &game->tex.so);
	img_free(game, &game->tex.we);
	img_free(game, &game->tex.ea);
	img_free(game, &game->frame);
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
#ifdef __linux__
	if (game->mlx)
		mlx_destroy_display(game->mlx);
#endif
	game->mlx = NULL;
}

int	game_run(t_game *game)
{
	if (!game->mlx || !game->win)
		return (printf("invalid game\n"));
	mlx_loop(game->mlx);
	return (0);
}
