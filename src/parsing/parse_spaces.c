/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:21:30 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 17:21:31 by aboukent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	convert_line_spaces(char *line, int first, int last)
{
	int	x;

	x = first;
	while (x <= last)
	{
		if (line[x] == ' ' || line[x] == '\t')
			line[x] = '0';
		x++;
	}
}

void	find_space_bounds(char *line, int len, int *first, int *last)
{
	*first = 0;
	while (*first < len && (line[*first] == ' ' || line[*first] == '\t'))
		(*first)++;
	*last = len - 1;
	while (*last >= 0 && (line[*last] == ' ' || line[*last] == '\t'))
		(*last)--;
}

void	convert_spaces_to_floor(t_map *map)
{
	int	y;
	int	first_nonspace;
	int	last_nonspace;
	int	len;

	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->map[y]);
		find_space_bounds(map->map[y], len, &first_nonspace, &last_nonspace);
		convert_line_spaces(map->map[y], first_nonspace, last_nonspace);
		y++;
	}
}
