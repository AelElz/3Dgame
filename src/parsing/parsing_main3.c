/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:00:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/15 18:54:37 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	validate_map_char_in_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != '\n' && line[j] != '\r'
			&& !is_valid_map_char(line[j]))
		{
			printf("Error: Invalid character '%c' in map\n", line[j]);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	check_empty_line(char **lines, int i, int count)
{
	if (i + 1 < count && lines[i + 1]
		&& !is_empty_or_whitespace(lines[i + 1]))
	{
		printf("Error: Empty line within map (line %d)\n", i + 1);
		return (0);
	}
	return (1);
}

static int	process_line(char **lines, int i, int *started, int *empty)
{
	if (!is_empty_or_whitespace(lines[i]))
	{
		*empty = 0;
		if (is_map_line(lines[i]))
		{
			*started = 1;
			if (!validate_map_char_in_line(lines[i]))
				return (0);
		}
		else if (*started)
		{
			printf("Error: Invalid content after map starts: '%s'\n", lines[i]);
			return (0);
		}
	}
	else if (*started)
	{
		(*empty)++;
		return (check_empty_line(lines, i, 0));
	}
	return (1);
}

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
			if (!is_empty_or_whitespace(lines[i + 1]))
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
