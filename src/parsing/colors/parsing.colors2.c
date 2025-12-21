/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.colors2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:43:57 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/21 20:01:00 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	parse_ceiling_color(t_map *map, char *line)
{
	if (map->ceiling_color)
	{
		printf("Error\nDuplicate C color found\n");
		return (0);
	}
	map->ceiling_color = extract_color(line);
	return (1);
}

int	parse_floor_color(t_map *map, char *line)
{
	if (map->floor_color)
	{
		printf("Error\nDuplicate F color found\n");
		return (0);
	}
	map->floor_color = extract_color(line);
	return (1);
}

int	validate_color(char *color, char *name, char *type)
{
	if (!color)
	{
		printf("Error: Missing %s (%s) color\n", name, type);
		return (0);
	}
	if (!validate_color_format(color))
	{
		printf("Error: Invalid %s color format: %s\n", type, color);
		return (0);
	}
	return (1);
}

int	validate_all_colors(t_map *map)
{
	int	valid;

	valid = 1;
	if (!validate_color(map->floor_color, "F", "Floor"))
		valid = 0;
	if (!validate_color(map->ceiling_color, "C", "Ceiling"))
		valid = 0;
	return (valid);
}
