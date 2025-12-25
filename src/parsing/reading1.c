/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:23:12 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 22:55:43 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*extract_line(char *content, int *pos)
{
	int		start;
	int		len;
	char	*line;

	start = *pos;
	len = 0;
	while (content[*pos] && content[*pos] != '\n')
	{
		(*pos)++;
		len++;
	}
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, content + start, len);
	line[len] = '\0';
	if (content[*pos] == '\n')
		(*pos)++;
	return (line);
}

char	**allocate_and_fill_lines(char *content, int count, int *lc)
{
	char	**lines;
	int		pos;
	int		i;

	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < count)
	{
		lines[i] = extract_line(content, &pos);
		if (!lines[i])
		{
			while (--i >= 0)
				free(lines[i]);
			free(lines);
			return (NULL);
		}
		i++;
	}
	lines[i] = NULL;
	*lc = count;
	return (lines);
}

char	**split_lines(char *content, int *line_count)
{
	int		count;

	count = count_lines_in_content(content);
	return (allocate_and_fill_lines(content, count, line_count));
}
