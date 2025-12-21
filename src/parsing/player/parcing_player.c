/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:42:53 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/21 20:18:23 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	init_directions(int *dx, int *dy)
{
	dx[0] = 1;
	dy[0] = 0;
	dx[1] = -1;
	dy[1] = 0;
	dx[2] = 0;
	dy[2] = 1;
	dx[3] = 0;
	dy[3] = -1;
}

void	set_player_angle(t_map *map, char c)
{
	if (c == 'N')
		map->player.angle = 270.0;
	else if (c == 'S')
		map->player.angle = 90.0;
	else if (c == 'W')
		map->player.angle = 180.0;
	else if (c == 'E')
		map->player.angle = 0.0;
}

void	handle_player_spawn(t_map *map, int x, int y, int *player_count)
{
	if (*player_count > 0)
	{
		(*player_count)++;
		return ;
	}
	map->player.player_x = (double)x + 0.5;
	map->player.player_y = (double)y + 0.5;
	set_player_angle(map, map->map[y][x]);
	map->map[y][x] = '0';
	(*player_count)++;
}
