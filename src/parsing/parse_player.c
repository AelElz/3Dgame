#include "parsing.h"

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

void	process_player_found(t_map *map, int x, int y, int *pc)
{
	char	c;

	if (*pc > 0)
	{
		printf("Error: Multiple player spawn points found\n");
		exit(1);
	}
	c = map->map[y][x];
	map->player.player_x = (double)x + 0.5;
	map->player.player_y = (double)y + 0.5;
	set_player_angle(map, c);
	map->map[y][x] = '0';
	(*pc)++;
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
				*px = x;
				*py = y;
				process_player_found(map, x, y, pc);
			}
			x++;
		}
		y++;
	}
}
