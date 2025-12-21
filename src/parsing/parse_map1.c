/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:19:57 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 17:20:04 by aboukent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_empty_line(char **lines, int i, int count)
{
	if (i + 1 < count && lines[i + 1] && !is_empty(lines[i + 1]))
	{
		printf("Error: Empty line within map (line %d)\n", i + 1);
		return (0);
	}
	return (1);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

int	validate_map_char_in_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != '\n' && !is_valid_map_char(line[j]))
		{
			printf("Error: Invalid character '%c' in map\n", line[j]);
			return (0);
		}
		j++;
	}
	return (1);
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

int	process_line(char **lines, int i, int *started, int *empty)
{
	if (!is_empty(lines[i]))
	{
		*empty = 0;
		if (is_map_line(lines[i]))
		{
			*started = 1;
			if (!validate_map_char_in_line(lines[i]))
				return (0);
		}
		else if (*started)
		{
			printf("Error: Invalid content after map starts: '%s'\n", lines[i]);
			return (0);
		}
	}
	else if (*started)
	{
		(*empty)++;
		return (check_empty_line(lines, i, 0));
	}
	return (1);
}
