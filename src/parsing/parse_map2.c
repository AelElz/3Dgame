#include "parsing.h"

char	*pad_line(char *line, int target_width)
{
	char	*padded;
	int		len;
	int		i;

	len = ft_strlen(line);
	if (len >= target_width)
		return (ft_strdup(line));
	padded = malloc(target_width + 1);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
		padded[i++] = ' ';
	padded[i] = '\0';
	return (padded);
}

void	fill_map_array(t_map *map, char **lines, int start, int count)
{
	int	map_lines;
	int	i;

	map_lines = 0;
	i = start;
	while (i < count && lines[i])
	{
		if (is_map_line(lines[i]))
			map->map[map_lines++] = pad_line(lines[i], map->width);
		i++;
	}
	map->map[map_lines] = NULL;
}

int	calculate_max_width(char **lines, int start, int count)
{
	int	max_w;
	int	len;
	int	i;

	max_w = 0;
	i = start;
	while (i < count)
	{
		if (lines[i])
		{
			len = ft_strlen(lines[i]);
			if (len > max_w)
				max_w = len;
		}
		i++;
	}
	return (max_w);
}

int	count_map_lines(char **lines, int start_idx, int count)
{
	int	map_lines;
	int	i;

	map_lines = 0;
	i = start_idx;
	while (i < count && lines[i])
	{
		if (is_map_line(lines[i]))
			map_lines++;
		i++;
	}
	return (map_lines);
}
