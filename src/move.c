/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:40:33 by ayoub             #+#    #+#             */
/*   Updated: 2025/09/18 14:38:13 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_is_wall(const t_map *map, int mapX, int mapY)
{
	if (mapY < 0 || mapX < 0 || mapY >= map->height || mapX >= map->width)
		return (1);
	if (map->grid[mapY][mapX] == '1' || map->grid[mapY][mapX] == ' ')
		return (1);
	return (0);
}

void	try_to_move(t_game *game, double newX, double newY)
{
	int	colomX;
	int	colomY;

	colomX = (int)newX;
	colomY = (int)newY;
	if (!map_is_wall(&game->map, colomX, colomY))
		game->player.pos.y = newY;
}

void	move_fwd(t_game *game, double dist)
{
	double	newX;
	double	newY;

	newX = game->player.pos.x - game->player.dir.y * dist;
	newY = game->player.pos.y + game->player.dir.x * dist;
	try_to_move(game, newX, newY);
}

void	move_back(t_game *game, double dist)
{
	double	newX;
	double	newY;

	newX = game->player.pos.x + game->player.dir.y * dist;
	newY = game->player.pos.y - game->player.dir.x * dist;
	try_to_move(game, newX, newY);
}

void move_left(t_game *game, double dist)
{
	double newX = game->player.pos.x - game->player.dir.y * dist;
	double newY = game->player.pos.y + game->player.dir.x * dist;
	try_to_move(game, newX, newY);
}

void move_right(t_game *game, double dist)
{
	double newX = game->player.pos.x + game->player.dir.y * dist;
	double newY = game->player.pos.y - game->player.dir.x * dist;
	try_to_move(game, newX, newY);
}

void	turn_left(t_game *game, double angl)
{
	double	oldX;
	double	oldY;
	double	cosu;
	double	sinu;

	oldX = game->player.dir.x;
	oldY = game->player.dir.y;
	cosu = cos(-angl);
	sinu = sin(-angl);
	
	game->player.dir.x = oldX * cosu - oldY * sinu;
	game->player.dir.y = oldX * sinu + oldY * cosu;

	oldX = game->player.plane.x;
	oldY = game->player.plane.y;
	game->player.plane.x = oldX * cosu - oldY * sinu;
	game->player.plane.y = oldX * sinu + oldY * cosu;
}

void	turn_right(t_game *game, double angl)
{
	double	oldX;
	double	oldY;
	double	cosu;
	double	sinu;

	oldX = game->player.dir.x;
	oldY = game->player.dir.y;
	cosu = cos(angl);
	sinu = sin(angl);

	game->player.dir.x = oldX * cosu - oldY * sinu;
	game->player.dir.y = oldX * sinu - oldY * cosu;

	oldX = game->player.plane.x;
	oldY = game->player.plane.y;
	game->player.plane.x = oldX * cosu - oldY * sinu;
	game->player.plane.y = oldX * sinu + oldY * cosu;
}
