/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_closed1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:20:59 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 17:21:00 by aboukent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_neighbor_to_stack(t_flood_data *data, t_point neighbor, t_map *map)
{
	char	c;

	if (!data->visited[neighbor.y][neighbor.x])
	{
		c = map->map[neighbor.y][neighbor.x];
		if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			data->visited[neighbor.y][neighbor.x] = 1;
			data->stack[(*data->stack_size)++] = neighbor;
		}
	}
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

int	process_neighbors(t_map *map, t_point p, t_flood_data *data)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	nx;
	int	ny;

	init_directions(dx, dy);
	i = 0;
	while (i < 4)
	{
		nx = p.x + dx[i];
		ny = p.y + dy[i];
		if (check_boundary_escape(map, nx, ny))
		{
			*data->stack_size = 0;
			return (0);
		}
		if (ny >= 0 && ny < map->height && nx >= 0 && nx < map->width)
			add_neighbor_to_stack(data, (t_point){nx, ny}, map);
		i++;
	}
	return (1);
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
