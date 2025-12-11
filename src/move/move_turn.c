/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:00:20 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 22:00:27 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	turn_left(t_game *game, double ang)
{
	double	c;
	double	s;
	double	ox;
	double	oy;

	c = cos(ang);
	s = sin(ang);
	ox = game->player.dir.x;
	oy = game->player.dir.y;
	game->player.dir.x = ox * c - oy * s;
	game->player.dir.y = ox * s + oy * c;
	ox = game->player.plane.x;
	oy = game->player.plane.y;
	game->player.plane.x = ox * c - oy * s;
	game->player.plane.y = ox * s + oy * c;
}

void	turn_right(t_game *game, double ang)
{
	double	c;
	double	s;
	double	ox;
	double	oy;

	c = cos(-ang);
	s = sin(-ang);
	ox = game->player.dir.x;
	oy = game->player.dir.y;
	game->player.dir.x = ox * c - oy * s;
	game->player.dir.y = ox * s + oy * c;
	ox = game->player.plane.x;
	oy = game->player.plane.y;
	game->player.plane.x = ox * c - oy * s;
	game->player.plane.y = ox * s + oy * c;
}
