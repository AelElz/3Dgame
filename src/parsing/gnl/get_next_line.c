/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 08:53:54 by aboukent          #+#    #+#             */
/*   Updated: 2025/01/16 18:02:46 by aboukent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*before_nl(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_substr(buffer, 0, i + 1);
	else
		line = buffer;
	return (line);
}

char	*after_nl(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	line = NULL;
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	j = ft_strlen(buffer);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		line = ft_substr(buffer, i + 1, j - i);
		free(buffer);
	}
	return (line);
}

char	*get_read(int fd, char *buffer)
{
	char	*read_buffer;
	int		len;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	len = 0;
	while (1)
	{
		len = read(fd, read_buffer, BUFFER_SIZE);
		if (len == -1)
		{
			free(read_buffer);
			free(buffer);
			return (NULL);
		}
		else if (len == 0)
			break ;
		read_buffer[len] = '\0';
		buffer = ft_strjoin(buffer, read_buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(read_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = get_read(fd, buffer);
	line = before_nl(buffer);
	buffer = after_nl(buffer);
	return (line);
}
