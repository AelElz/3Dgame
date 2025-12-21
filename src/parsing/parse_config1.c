/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:19:11 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 17:19:17 by aboukent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*copy_string(char *src, int len)
{
	char	*dest;
	int		i;

	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	parse_no_texture(t_map *map, char *line)
{
	if (map->no_texture)
	{
		printf("Error: Multiple NO texture found\n");
		return (0);
	}
	map->no_texture = extract_path(line);
	return (1);
}

int	parse_so_texture(t_map *map, char *line)
{
	if (map->so_texture)
	{
		printf("Error: Multiple SO texture found\n");
		return (0);
	}
	map->so_texture = extract_path(line);
	return (1);
}

int	parse_we_texture(t_map *map, char *line)
{
	if (map->we_texture)
	{
		printf("Error: Multiple WE texture found\n");
		return (0);
	}
	map->we_texture = extract_path(line);
	return (1);
}

int	parse_ea_texture(t_map *map, char *line)
{
	if (map->ea_texture)
	{
		printf("Error: Multiple EA texture found\n");
		return (0);
	}
	map->ea_texture = extract_path(line);
	return (1);
}
