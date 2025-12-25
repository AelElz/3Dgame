/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:45:58 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/22 02:45:31 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map_arrays(t_game *game)
{
	int	i;

	if (game->map.map)
	{
		i = 0;
		while (game->map.map[i])
			free(game->map.map[i++]);
		free(game->map.map);
	}
	if (game->map.grid)
	{
		i = 0;
		while (game->map.grid[i])
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
}

void	free_texture_paths(t_game *game)
{
	if (game->map.no_texture)
		free(game->map.no_texture);
	if (game->map.so_texture)
		free(game->map.so_texture);
	if (game->map.we_texture)
		free(game->map.we_texture);
	if (game->map.ea_texture)
		free(game->map.ea_texture);
	if (game->map.floor_color)
		free(game->map.floor_color);
	if (game->map.ceiling_color)
		free(game->map.ceiling_color);
}

void	game_free(t_game *game)
{
	img_free(game, &game->tex.no);
	img_free(game, &game->tex.so);
	img_free(game, &game->tex.we);
	img_free(game, &game->tex.ea);
	img_free(game, &game->frame);
	free_map_arrays(game);
	free_texture_paths(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

int	game_run(t_game *game)
{
	if (!game->mlx || !game->win)
		return (printf("invalid game\n"));
	mlx_loop(game->mlx);
	return (0);
}
