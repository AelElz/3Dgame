/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:00:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/19 17:04:12 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	find_map_start(char **lines, int line_count)
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

static int	process_map_data(t_map *map, char **lines, int i, int line_count)
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
		printf("Error\nMap is not properly enclosed by walls\n");
		return (0);
	}
	convert_spaces_to_floor(map);
	if (!validate_and_set_player(map))
		return (0);
	return (1);
}

static char	**read_and_split_file(const char *cub_path, int *line_count)
{
	char	*content;
	char	**lines;

	content = read_entire_file(cub_path);
	if (!content)
	{
		printf("Error: Could not read file %s\n", cub_path);
		return (NULL);
	}
	lines = split_lines(content, line_count);
	free(content);
	if (!lines)
		printf("Error: Could not split lines\n");
	return (lines);
}

static int	handle_map_processing(t_map *map, char **lines, int line_count)
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

int	read_cub_file(const char *cub_path, t_map *map)
{
	char	**lines;
	int		line_count;

	lines = read_and_split_file(cub_path, &line_count);
	if (!lines)
		return (0);
	map->map = lines;
	if (!parse_map_config(map))
	{
		map->map = NULL;
		cleanup_lines(lines, line_count);
		printf("Error: Failed to parse config\n");
		return (0);
	}
	if (!handle_map_processing(map, lines, line_count))
		return (0);
	map->player_set = 1;
	return (1);
}
