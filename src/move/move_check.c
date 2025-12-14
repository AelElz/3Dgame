/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:59:38 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/14 15:06:04 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_is_wall(const t_map *map, int mx, int my)
{
	char	**grid;

	if (my < 0 || mx < 0 || my >= map->height || mx >= map->width)
		return (1);
	grid = map->grid;
	if (!grid)
		grid = map->map;
	if (!grid || !grid[my])
		return (1);
	return (grid[my][mx] == '1' || grid[my][mx] == ' ');
}

int	is_valid_pos(const t_map *map, double x, double y)
{
	double	radius;
	int		mx;
	int		my;

	radius = 0.20;
	mx = (int)x;
	my = (int)y;
	if (map_is_wall(map, mx, my))
		return (0);
	if (map_is_wall(map, (int)(x + radius), (int)y))
		return (0);
	if (map_is_wall(map, (int)(x - radius), (int)y))
		return (0);
	if (map_is_wall(map, (int)x, (int)(y + radius)))
		return (0);
	if (map_is_wall(map, (int)x, (int)(y - radius)))
		return (0);
	return (1);
}

void	try_move(t_game *game, double new_x, double new_y)
{
	double	old_x;
	double	old_y;
	int		can_move_both;

	old_x = game->player.pos.x;
	old_y = game->player.pos.y;
	can_move_both = is_valid_pos(&game->map, new_x, new_y);
	if (can_move_both)
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
	else
	{
		if (is_valid_pos(&game->map, new_x, old_y))
			game->player.pos.x = new_x;
		if (is_valid_pos(&game->map, old_x, new_y))
			game->player.pos.y = new_y;
	}
}
