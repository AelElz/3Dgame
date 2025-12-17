/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:42:57 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/17 22:11:00 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

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

char	*trim_end_spaces(char *start, char *end)
{
	while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
		end--;
	return (end);
}

char	*extract_path(char *line)
{
	char	*start;
	char	*end;
	int		len;

	start = line;
	while (*start && (*start == ' ' || *start == '\t'
			|| (*start >= 'A' && *start <= 'Z')))
		start++;
	start = skip_spaces(start);
	if (!*start || *start == '\n')
		return (NULL);
	end = start;
	while (*end && *end != ' ' && *end != '\t' && *end != '\n' && *end != '\r')
		end++;
	len = end - start;
	if (len == 0)
		return (NULL);
	return (copy_string(start, len));
}
