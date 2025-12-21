/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:22:14 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 17:22:15 by aboukent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_valid_xpm_path(const char *path)
{
	int		len;
	int		fd;
	char	buf[1];

	if (!path)
		return (0);
	len = ft_strlen((char *)path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	if (read(fd, buf, 1) <= 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	validate_texture(char *texture, char *name, char *dir)
{
	if (!texture)
	{
		printf("Error: Missing %s (%s) texture\n", name, dir);
		return (0);
	}
	if (!is_valid_xpm_path(texture))
	{
		printf("Error: %s texture invalid or not found: %s\n", name, texture);
		return (0);
	}
	return (1);
}

int	validate_all_textures(t_map *map)
{
	int	valid;

	valid = 1;
	if (!validate_texture(map->no_texture, "NO", "North"))
		valid = 0;
	if (!validate_texture(map->so_texture, "SO", "South"))
		valid = 0;
	if (!validate_texture(map->we_texture, "WE", "West"))
		valid = 0;
	if (!validate_texture(map->ea_texture, "EA", "East"))
		valid = 0;
	return (valid);
}

int	validate_parsing_completeness(t_map *map)
{
	int	valid_textures;
	int	valid_colors;

	valid_textures = validate_all_textures(map);
	valid_colors = validate_all_colors(map);
	return (valid_textures && valid_colors);
}
