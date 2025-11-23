/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:59:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 22:00:18 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_fwd(t_game *game, double dist)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.x * dist;
	new_y = game->player.pos.y + game->player.dir.y * dist;
	try_move(game, new_x, new_y);
}

void	move_back(t_game *game, double dist)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.dir.x * dist;
	new_y = game->player.pos.y - game->player.dir.y * dist;
	try_move(game, new_x, new_y);
}

void	move_left(t_game *game, double dist)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.y * dist;
	new_y = game->player.pos.y - game->player.dir.x * dist;
	try_move(game, new_x, new_y);
}

void	move_right(t_game *game, double dist)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.dir.y * dist;
	new_y = game->player.pos.y + game->player.dir.x * dist;
	try_move(game, new_x, new_y);
}
