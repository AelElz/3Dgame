/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:30:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/17 22:10:54 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	find_space_bounds(char *line, int len, int *first, int *last)
{
	*first = 0;
	while (*first < len && (line[*first] == ' ' || line[*first] == '\t'))
		(*first)++;
	*last = len - 1;
	while (*last >= 0 && (line[*last] == ' ' || line[*last] == '\t'))
		(*last)--;
}

static void	convert_line_spaces(char *line, int first, int last)
{
	int	x;

	x = first;
	while (x <= last)
	{
		if (line[x] == ' ' || line[x] == '\t')
			line[x] = '0';
		x++;
	}
}

void	convert_spaces_to_floor(t_map *map)
{
	int	y;
	int	first_nonspace;
	int	last_nonspace;
	int	len;

	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->map[y]);
		find_space_bounds(map->map[y], len, &first_nonspace, &last_nonspace);
		convert_line_spaces(map->map[y], first_nonspace, last_nonspace);
		y++;
	}
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
