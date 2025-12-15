/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:00:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/15 18:46:04 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	calculate_max_width(char **lines, int start, int count)
{
	int	max_w;
	int	len;
	int	i;

	max_w = 0;
	i = start;
	while (i < count)
	{
		if (lines[i])
		{
			len = ft_strlen(lines[i]);
			if (len > max_w)
				max_w = len;
		}
		i++;
	}
	return (max_w);
}

char	*pad_line(char *line, int target_width)
{
	char	*padded;
	int		len;
	int		i;

	len = ft_strlen(line);
	if (len >= target_width)
		return (ft_strdup(line));
	padded = malloc(target_width + 1);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
		padded[i++] = ' ';
	padded[i] = '\0';
	return (padded);
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

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

int	is_empty_or_whitespace(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
