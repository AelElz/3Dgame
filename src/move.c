/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:40:33 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/03 20:36:00 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_is_wall(const t_map *map, int mx, int my)
{
	if (my < 0 || mx < 0 || my >= map->height || mx >= map->width)
		return (1);
	return (map->grid[my][mx] == '1' || map->grid[my][mx] == ' ');
}

static int can_move_to(const t_map *map, double x, double y)
{
	const double r = 0.20;
	int cx = (int)(x);
	int cy = (int)(y);

	if (map_is_wall(map, cx, cy))
		return (0);

	if (map_is_wall(map, (int)(x - r), cy)) return (0);
	if (map_is_wall(map, (int)(x + r), cy)) return (0);
	if (map_is_wall(map, cx, (int)(y - r))) return (0);
	if (map_is_wall(map, cx, (int)(y + r))) return (0);

	return (1);
}

static void try_move(t_game *game, double newX, double newY)
{
	if (can_move_to(&game->map, newX, game->player.pos.y))
		game->player.pos.x = newX;

	if (can_move_to(&game->map, game->player.pos.x, newY))
		game->player.pos.y = newY;
}

void	move_fwd(t_game *game, double dist)
{
	const double nx = game->player.pos.x + game->player.dir.x * dist;
	const double ny = game->player.pos.y + game->player.dir.y * dist;
	try_move(game, nx, ny);
}

void	move_back(t_game *game, double dist)
{
	const double nx = game->player.pos.x - game->player.dir.x * dist;
	const double ny = game->player.pos.y - game->player.dir.y * dist;
	try_move(game, nx, ny);
}

void	move_left(t_game *game, double dist)
{
	const double nx = game->player.pos.x - game->player.plane.x * dist;
	const double ny = game->player.pos.y - game->player.plane.y * dist;
	try_move(game, nx, ny);
}

void	move_right(t_game *game, double dist)
{
	const double nx = game->player.pos.x + game->player.plane.x * dist;
	const double ny = game->player.pos.y + game->player.plane.y * dist;
	try_move(game, nx, ny);
}

void	turn_left(t_game *game, double ang)
{
	const double c = cos(ang);
	const double s = sin(ang);
	double ox, oy;

	ox = game->player.dir.x; oy = game->player.dir.y;
	game->player.dir.x = ox * c - oy * s;
	game->player.dir.y = ox * s + oy * c;

	ox = game->player.plane.x; oy = game->player.plane.y;
	game->player.plane.x = ox * c - oy * s;
	game->player.plane.y = ox * s + oy * c;
}

void	turn_right(t_game *game, double ang)
{
	const double c = cos(-ang);
	const double s = sin(-ang);
	double ox, oy;

	ox = game->player.dir.x; oy = game->player.dir.y;
	game->player.dir.x = ox * c - oy * s;
	game->player.dir.y = ox * s + oy * c;

	ox = game->player.plane.x; oy = game->player.plane.y;
	game->player.plane.x = ox * c - oy * s;
	game->player.plane.y = ox * s + oy * c;
}
