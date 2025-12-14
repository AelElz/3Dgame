/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:43:48 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/14 14:46:38 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	check_map_closed(t_map *map, int start_x, int start_y)
{
	t_flood_data	data;
	int				stack_size;
	int				result;

	data.visited = allocate_visited(map);
	if (!data.visited)
		return (0);
	data.stack = allocate_stack(map, data.visited);
	if (!data.stack)
		return (0);
	stack_size = 0;
	data.stack_size = &stack_size;
	data.stack[stack_size++] = (t_point){start_x, start_y};
	data.visited[start_y][start_x] = 1;
	result = flood_fill_loop(map, &data);
	free(data.stack);
	free_visited(data.visited, map);
	return (result);
}

void	cleanup_map_array(t_map *map)
{
	int	i;

	if (!map->map)
		return ;
	i = 0;
	while (i < map->height && map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

int	check_map_borders(t_map *map)
{
	if (!map || !map->map || map->height == 0)
		return (0);
	if (!check_first_row(map))
		return (0);
	if (!check_last_row(map))
		return (0);
	if (!check_middle_rows(map))
		return (0);
	return (1);
}

void	process_map_char(t_map *map, int x, int y, int *player_count)
{
	char	c;

	c = map->map[y][x];
	if (c == '1' || c == '0')
		return ;
	else if (c == ' ' || c == '\t')
		map->map[y][x] = '0';
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		handle_player_spawn(map, x, y, player_count);
	else
	{
		printf("Error\nInvalid character '%c' in map at (%d,%d)\n", c, y, x);
		exit(1);
	}
}

void	scan_map_for_player(t_map *map, int *pc, int *px, int *py)
{
	int		x;
	int		y;
	char	c;

	*pc = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x])
		{
			c = map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				if (*pc > 0)
				{
					printf("Error\nMultiple player spawn points found\n");
					exit(1);
				}
				*px = x;
				*py = y;
				map->player.player_x = (double)x + 0.5;
				map->player.player_y = (double)y + 0.5;
				set_player_angle(map, c);
				map->map[y][x] = '0';
				(*pc)++;
			}
			x++;
		}
		y++;
	}
}

int	validate_and_set_player(t_map *map)
{
	int	player_count;
	int	player_x;
	int	player_y;

	scan_map_for_player(map, &player_count, &player_x, &player_y);
	if (player_count != 1)
	{
		if (player_count == 0)
			printf("Error\nNo player spawn point found\n");
		else
			printf("Error\nMultiple player spawn points found\n");
		return (0);
	}
	return (1);
}
