#include "parsing.h"

int	validate_row_borders(t_map *map, int y, int len)
{
	int	first_char;
	int	last_char;

	first_char = find_first_nonspace(map->map[y], len);
	last_char = find_last_nonspace(map->map[y], len);
	if (!check_row_borders(map, y, first_char, last_char))
		return (0);
	return (1);
}

int	check_middle_rows(t_map *map)
{
	int	y;
	int	len;

	y = 0;
	while (y < map->height)
	{
		if (should_skip_row(map, y, &len))
		{
			y++;
			continue ;
		}
		if (!validate_row_borders(map, y, len))
			return (0);
		y++;
	}
	return (1);
}

int	check_last_row(t_map *map)
{
	int		x;
	char	c;

	x = 0;
	while (map->map[map->height - 1][x] && map->map[map->height - 1][x] != '\n')
	{
		c = map->map[map->height - 1][x];
		if (c != '1' && c != ' ' && c != '\t')
		{
			printf("Error: Last row must only contain walls\n");
			return (0);
		}
		x++;
	}
	return (1);
}

int	check_first_row(t_map *map)
{
	int		x;
	char	c;

	x = 0;
	while (map->map[0][x] && map->map[0][x] != '\n')
	{
		c = map->map[0][x];
		if (c != '1' && c != ' ' && c != '\t')
		{
			printf("Error: First row must only contain walls\n");
			return (0);
		}
		x++;
	}
	return (1);
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
