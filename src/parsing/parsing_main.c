/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/14 14:44:58 by ael-azha         ###   ########.fr       */
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

char	**split_lines(char *content, int *line_count)
{
	char	**lines;
	int		count;

	lines = ft_split(content, '\n');
	if (!lines)
		return (NULL);
	count = 0;
	while (lines[count])
		count++;
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

int	parse_map_section(t_map *map, char **lines, int start_idx, int count)
{
	int		map_lines;
	int		i;
	int		max_width;

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
	if (!validate_and_set_player(map))
		return (0);
	i = 0;
	while (i < line_count && lines[i])
		free(lines[i++]);
	free(lines);
	map->player_set = 1;
	return (1);
}
