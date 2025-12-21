#include "parsing.h"

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
	return (1);
}
