/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:21:51 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 22:23:40 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*trim_end_spaces(char *start, char *end)
{
	while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
		end--;
	return (end);
}

char	*extract_color(char *line)
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
	while (*end && *end != '\n' && *end != '\r')
		end++;
	end = trim_end_spaces(start, end);
	len = end - start;
	if (len == 0)
		return (NULL);
	return (copy_string(start, len));
}

char	*skip_to_comma(char *ptr)
{
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
		ptr++;
	if (*ptr != ',')
		return (NULL);
	return (ptr + 1);
}

char	*parse_rgb_value(char *ptr, int *value, int *has_digits)
{
	*value = 0;
	*has_digits = 0;
	while (*ptr && *ptr >= '0' && *ptr <= '9')
	{
		*value = *value * 10 + (*ptr++ - '0');
		*has_digits = 1;
		if (*value > 255)
			break ;
	}
	return (ptr);
}

int	validate_rgb_component(char **ptr)
{
	int	value;
	int	has_digits;

	*ptr = parse_rgb_value(*ptr, &value, &has_digits);
	if (!has_digits || value > 255)
		return (0);
	*ptr = skip_spaces(*ptr);
	return (1);
}
