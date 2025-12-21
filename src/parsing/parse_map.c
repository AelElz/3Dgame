#include "parsing.h"

int	validate_map_continuity(char **lines, int start_idx, int count)
{
	int		i;
	int		map_started;
	int		consecutive_empty;

	map_started = 0;
	consecutive_empty = 0;
	i = start_idx;
	while (i < count && lines[i])
	{
		if (!process_line(lines, i, &map_started, &consecutive_empty))
			return (0);
		if (consecutive_empty && i + 1 < count && lines[i + 1])
		{
			if (!is_empty(lines[i + 1]))
			{
				printf("Error: Empty line within map (line %d)\n", i + 1);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	parse_map_section(t_map *map, char **lines, int start_idx, int count)
{
	int		map_lines;
	int		max_width;

	if (!validate_map_continuity(lines, start_idx, count))
		return (0);
	map_lines = count_map_lines(lines, start_idx, count);
	if (map_lines == 0)
		return (0);
	max_width = calculate_max_width(lines, start_idx, count);
	map->width = max_width;
	map->map = malloc(sizeof(char *) * (map_lines + 1));
	map->height = map_lines;
	fill_map_array(map, lines, start_idx, count);
	return (1);
}

int	process_map_data(t_map *map, char **lines, int i, int line_count)
{
	if (!parse_map_section(map, lines, i, line_count))
	{
		printf("Error: No valid map found\n");
		return (0);
	}
	if (!validate_parsing_completeness(map))
		return (0);
	if (!check_map_borders(map))
	{
		printf("Error: Map is not properly enclosed\n");
		return (0);
	}
	convert_spaces_to_floor(map);
	if (!validate_and_set_player(map))
		return (0);
	return (1);
}

int	find_map_start(char **lines, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count && lines[i])
	{
		if (*skip_spaces(lines[i]) == '1' || *skip_spaces(lines[i]) == '0')
			break ;
		i++;
	}
	return (i);
}

int	parse_map(t_map *map, char **lines, int line_count)
{
	int	i;

	i = find_map_start(lines, line_count);
	if (!process_map_data(map, lines, i, line_count))
	{
		if (map->map != lines)
			cleanup_lines(map->map, map->height);
		map->map = NULL;
		cleanup_lines(lines, line_count);
		return (0);
	}
	cleanup_lines(lines, line_count);
	return (1);
}
