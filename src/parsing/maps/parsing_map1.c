/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:43:15 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/15 17:43:04 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	get_map_char(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (' ');
	if (!map->map[y] || x >= (int)ft_strlen(map->map[y]))
		return (' ');
	return (map->map[y][x]);
}

int	check_boundary_escape(t_map *map, int nx, int ny)
{
	char	c;

	if (ny < 0 || ny >= map->height)
		return (1);
	if (nx < 0 || nx >= map->width)
		return (1);
	if (!map->map[ny])
		return (1);
	c = map->map[ny][nx];
	if (c == ' ' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

int	flood_fill_loop(t_map *map, t_flood_data *data)
{
	t_point	current;

	while (*data->stack_size > 0)
	{
		current = data->stack[--(*data->stack_size)];
		if (!process_neighbors(map, current, data))
			return (0);
	}
	return (1);
}
