/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/17 22:10:35 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*read_entire_file(const char *path)
{
	int		fd;
	char	buf[1024];
	char	*content;
	char	*tmp;
	int		bytes;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	bytes = read(fd, buf, 1023);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		tmp = ft_strjoin(content, buf);
		free(content);
		content = tmp;
		bytes = read(fd, buf, 1023);
	}
	close(fd);
	return (content);
}

static int	count_lines_in_content(char *content)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && content[i - 1] != '\n')
		count++;
	return (count);
}

static char	*extract_line(char *content, int *pos)
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

static char	**allocate_and_fill_lines(char *content, int count, int *lc)
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
