#include "parsing.h"

char	*extract_path(char *line)
{
	char	*start;
	char	*end;
	int		len;

	start = line;
	while (*start && (*start == ' ' || *start == '\t'
			|| (*start >= 'A' && *start <= 'Z')))
		start++;
	start = skip_spaces(start);
	if (!*start || *start == '\n')
		return (NULL);
	end = start;
	while (*end && *end != ' ' && *end != '\t' && *end != '\n')
		end++;
	len = end - start;
	if (len == 0)
		return (NULL);
	return (copy_string(start, len));
}

int	parse_ceiling_color(t_map *map, char *line)
{
	if (map->ceiling_color)
	{
		printf("Error: Multiple C color found\n");
		return (0);
	}
	map->ceiling_color = extract_path(line);
	return (1);
}

int	parse_floor_color(t_map *map, char *line)
{
	if (map->floor_color)
	{
		printf("Error: Multiple F color found\n");
		return (0);
	}
	map->floor_color = extract_path(line);
	return (1);
}

int	parse_config_line(t_map *map, char *line)
{
	skip_spaces(line);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_no_texture(map, line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_so_texture(map, line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_we_texture(map, line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_ea_texture(map, line));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_floor_color(map, line));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_ceiling_color(map, line));
	else if (*line == '1' || *line == '0')
		return (-1);
	return (1);
}

int	parse_config(t_map *map)
{
	int		i;
	char	*line;
	int		result;

	if (!map || !map->map)
		return (0);
	i = 0;
	while (map->map[i])
	{
		line = skip_spaces(map->map[i]);
		if (!*line || *line == '\n')
		{
			i++;
			continue ;
		}
		result = parse_config_line(map, line);
		if (result == 0)
			return (0);
		if (result == -1)
			break ;
		i++;
	}
	return (1);
}
