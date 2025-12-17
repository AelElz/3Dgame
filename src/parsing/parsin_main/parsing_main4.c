/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:00:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/17 22:10:50 by ael-azha         ###   ########.fr       */
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

static void	cleanup_lines(char **lines, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count && lines[i])
		free(lines[i++]);
	free(lines);
}

int	read_cub_file(const char *cub_path, t_map *map)
{
	char	**lines;
	int		line_count;
	int		i;
	char	*content;

	content = read_entire_file(cub_path);
	if (!content)
		return (printf("Error: Could not read file %s\n", cub_path), 0);
	lines = split_lines(content, &line_count);
	free(content);
	if (!lines)
		return (printf("Error: Could not open file %s\n", cub_path), 0);
	map->map = lines;
	if (!parse_map_config(map))
		return (printf("Error: Failed to parse config\n"), 0);
	i = find_map_start(lines, line_count);
	if (!process_map_data(map, lines, i, line_count))
		return (0);
	cleanup_lines(lines, line_count);
	map->player_set = 1;
	return (1);
}
