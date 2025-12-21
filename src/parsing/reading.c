/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:23:22 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 17:23:23 by aboukent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*read_all_file(char *file)
{
	int		fd;
	char	buf[1024];
	char	*content;
	char	*tmp;
	int		bytes;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	bytes = read(fd, buf, 1023);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		tmp = ft_strjoin(content, buf);
		free(content);
		content = tmp;
		bytes = read(fd, buf, 1023);
	}
	close(fd);
	return (content);
}

char	**read_and_split_file(char *file, int *line_count)
{
	char	*content;
	char	**lines;

	content = read_all_file(file);
	if (!content)
	{
		printf("Error: Could not read file %s\n", file);
		return (NULL);
	}
	lines = split_lines(content, line_count);
	free(content);
	if (!lines)
		printf("Error: Could not split lines\n");
	return (lines);
}

int	read_file(char *file, t_map *map)
{
	char	**lines;
	int		line_count;

	lines = read_and_split_file(file, &line_count);
	if (!lines)
		return (0);
	map->map = lines;
	if (!parse_config(map))
	{
		map->map = NULL;
		cleanup_lines(lines, line_count);
		printf("Error: Failed to parse config\n");
		return (0);
	}
	if (!parse_map(map, lines, line_count))
		return (0);
	map->player_set = 1;
	return (1);
}
