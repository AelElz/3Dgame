/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/15 17:54:17 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*read_entire_file(const char *path)
{
	int		fd;
	char	buf[1024];
	char	*content;
	char	*tmp;
	int		bytes;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	while ((bytes = read(fd, buf, 1023)) > 0)
	{
		buf[bytes] = '\0';
		tmp = ft_strjoin(content, buf);
		free(content);
		content = tmp;
	}
	close(fd);
	return (content);
}

static int	count_lines_in_content(char *content)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && content[i - 1] != '\n')
		count++;
	return (count);
}

static char	*extract_line(char *content, int *pos)
{
	int		start;
	int		len;
	char	*line;

	start = *pos;
	len = 0;
	while (content[*pos] && content[*pos] != '\n')
	{
		(*pos)++;
		len++;
	}
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, content + start, len);
	line[len] = '\0';
	if (content[*pos] == '\n')
		(*pos)++;
	return (line);
}

char	**split_lines(char *content, int *line_count)
{
	char	**lines;
	int		count;
	int		pos;
	int		i;

	count = count_lines_in_content(content);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < count)
	{
		lines[i] = extract_line(content, &pos);
		if (!lines[i])
		{
			while (--i >= 0)
				free(lines[i]);
			free(lines);
			return (NULL);
		}
		i++;
	}
	lines[i] = NULL;
	*line_count = count;
	return (lines);
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

int	is_map_line(char *line)
{
	char	*s;

	if (!line)
		return (0);
	s = skip_spaces(line);
	if (*s == '1' || *s == '0')
		return (1);
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

int	is_empty_or_whitespace(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	validate_map_continuity(char **lines, int start_idx, int count)
{
	int		i;
	int		map_started;
	int		j;
	int		consecutive_empty;

	map_started = 0;
	consecutive_empty = 0;
	i = start_idx;
	while (i < count && lines[i])
	{
		if (!is_empty_or_whitespace(lines[i]))
		{
			consecutive_empty = 0;
			if (is_map_line(lines[i]))
			{
				map_started = 1;
				j = 0;
				while (lines[i][j])
				{
					if (lines[i][j] != '\n' && lines[i][j] != '\r'
						&& !is_valid_map_char(lines[i][j]))
					{
						printf("Error: Invalid character '%c' in map\n", lines[i][j]);
						return (0);
					}
					j++;
				}
			}
			else if (map_started)
			{
				printf("Error: Invalid content after map starts: '%s'\n", lines[i]);
				return (0);
			}
		}
		else if (map_started)
		{
			consecutive_empty++;
			if (i + 1 < count && lines[i + 1] 
				&& !is_empty_or_whitespace(lines[i + 1]))
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
	int		i;
	int		max_width;

	if (!validate_map_continuity(lines, start_idx, count))
		return (0);
	map_lines = 0;
	i = start_idx;
	while (i < count && lines[i])
	{
		if (is_map_line(lines[i]))
			map_lines++;
		i++;
	}
	if (map_lines == 0)
		return (0);
	max_width = calculate_max_width(lines, start_idx, count);
	map->width = max_width;
	map->map = malloc(sizeof(char *) * (map_lines + 1));
	map->height = map_lines;
	map_lines = 0;
	i = start_idx;
	while (i < count && lines[i])
	{
		if (is_map_line(lines[i]))
			map->map[map_lines++] = pad_line(lines[i], max_width);
		i++;
	}
	map->map[map_lines] = NULL;
	return (1);
}

void	convert_spaces_to_floor(t_map *map)
{
	int	x;
	int	y;
	int	first_nonspace;
	int	last_nonspace;
	int	len;

	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->map[y]);
		first_nonspace = 0;
		while (first_nonspace < len && (map->map[y][first_nonspace] == ' '
				|| map->map[y][first_nonspace] == '\t'))
			first_nonspace++;
		last_nonspace = len - 1;
		while (last_nonspace >= 0 && (map->map[y][last_nonspace] == ' '
				|| map->map[y][last_nonspace] == '\t'))
			last_nonspace--;
		x = first_nonspace;
		while (x <= last_nonspace)
		{
			if (map->map[y][x] == ' ' || map->map[y][x] == '\t')
				map->map[y][x] = '0';
			x++;
		}
		y++;
	}
}

int	read_cub_file(const char *cub_path, t_map *map)
{
	char	**lines;
	int		line_count;
	int		i;
	char	*content;

	content = read_entire_file(cub_path);
	if (!content)
	{
		printf("Error: Could not read file %s\n", cub_path);
		return (0);
	}
	lines = split_lines(content, &line_count);
	free(content);
	if (!lines)
	{
		printf("Error: Could not open file %s\n", cub_path);
		return (0);
	}
	map->map = lines;
	if (!parse_map_config(map))
	{
		printf("Error: Failed to parse config\n");
		return (0);
	}
	i = 0;
	while (i < line_count && lines[i])
	{
		if (*skip_spaces(lines[i]) == '1' || *skip_spaces(lines[i]) == '0')
			break ;
		i++;
	}
	if (!parse_map_section(map, lines, i, line_count))
	{
		printf("Error: No valid map found\n");
		return (0);
	}
	if (!validate_parsing_completeness(map))
		return (0);
	if (!check_map_borders(map))
	{
		printf("Error\nMap is not properly enclosed by walls\n");
		return (0);
	}
	convert_spaces_to_floor(map);
	if (!validate_and_set_player(map))
		return (0);
	i = 0;
	while (i < line_count && lines[i])
		free(lines[i++]);
	free(lines);
	map->player_set = 1;
	return (1);
}
