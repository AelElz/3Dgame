/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:45:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/15 18:40:10 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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
	if (!check_map_closed(map, player_x, player_y))
	{
		printf("Error\nMap is not closed - player can escape\n");
		return (0);
	}
	return (1);
}
