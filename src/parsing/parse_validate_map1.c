/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:22:30 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 17:22:31 by aboukent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_first_nonspace(char *row, int len)
{
	int	first_char;

	first_char = 0;
	while (first_char < len && (row[first_char] == ' '
			|| row[first_char] == '\t'))
		first_char++;
	return (first_char);
}

int	find_last_nonspace(char *row, int len)
{
	int	last_char;

	last_char = len - 1;
	while (last_char >= 0 && (row[last_char] == ' '
			|| row[last_char] == '\t'))
		last_char--;
	return (last_char);
}

int	check_row_borders(t_map *map, int y, int first_char, int last_char)
{
	if (first_char < get_row_length(map->map[y])
		&& map->map[y][first_char] != '1')
	{
		printf("Error: Row %d must start with a wall, found '%c'\n",
			y, map->map[y][first_char]);
		return (0);
	}
	if (last_char >= 0 && map->map[y][last_char] != '1')
	{
		printf("Error: Row %d must end with a wall, found '%c'\n",
			y, map->map[y][last_char]);
		return (0);
	}
	return (1);
}

int	get_row_length(char *row)
{
	int	len;

	len = 0;
	while (row[len] && row[len] != '\n')
		len++;
	return (len);
}

int	should_skip_row(t_map *map, int y, int *len)
{
	if (!map->map[y] || !*map->map[y])
		return (1);
	*len = get_row_length(map->map[y]);
	if (*len == 0)
		return (1);
	return (0);
}
