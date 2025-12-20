/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:42:53 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/20 14:51:59 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	cleanup_mlx(t_map *map)
{
	if (!map->mlx)
		return ;
	cleanup_mlx_images(map);
	if (map->win)
		mlx_destroy_window(map->mlx, map->win);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
}

void	cleanup_map(t_map *map)
{
	if (!map)
		return ;
	cleanup_textures(map);
	cleanup_map_array(map);
	cleanup_mlx(map);
	free(map);
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

char	**allocate_visited(t_map *map)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(char *) * map->height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = ft_calloc(map->width + 1, 1);
		if (!visited[i])
		{
			j = 0;
			while (j < i)
				free(visited[j++]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

void	free_visited(char **visited, t_map *map)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < map->height)
		free(visited[i++]);
	free(visited);
}
