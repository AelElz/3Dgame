/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:45:58 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/15 17:56:34 by ael-azha         ###   ########.fr       */
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
	if (game->map.map_full)
	{
		i = 0;
		while (game->map.map_full[i])
			free(game->map.map_full[i++]);
		free(game->map.map_full);
	}
	if (game->map.map)
	{
		i = 0;
		while (game->map.map[i])
			free(game->map.map[i++]);
		free(game->map.map);
	}
	if (game->map.tex_no)
		free(game->map.tex_no);
	if (game->map.tex_so)
		free(game->map.tex_so);
	if (game->map.tex_we)
		free(game->map.tex_we);
	if (game->map.tex_ea)
		free(game->map.tex_ea);
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
