#include "parsing.h"

int	check_color_chars(char *color_str, int *commas, int *num_count)
{
	int	i;

	i = 0;
	*commas = 0;
	*num_count = 0;
	while (color_str[i])
	{
		if (color_str[i] == ',')
			(*commas)++;
		else if (color_str[i] >= '0' && color_str[i] <= '9')
			(*num_count)++;
		else if (color_str[i] != ' ' && color_str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_basic_format(char *color_str, int *commas, int *num_count)
{
	if (!color_str || !check_color_chars(color_str, commas, num_count))
		return (0);
	if (*commas != 2 || *num_count < 3)
		return (0);
	return (1);
}

int	validate_color_format(char *color_str)
{
	int		commas;
	int		num_count;
	char	*ptr;

	if (!check_basic_format(color_str, &commas, &num_count))
		return (0);
	ptr = skip_spaces(color_str);
	if (!validate_rgb_component(&ptr))
		return (0);
	ptr = skip_to_comma(ptr);
	if (!ptr)
		return (0);
	ptr = skip_spaces(ptr);
	if (!validate_rgb_component(&ptr))
		return (0);
	ptr = skip_to_comma(ptr);
	if (!ptr)
		return (0);
	ptr = skip_spaces(ptr);
	if (!validate_rgb_component(&ptr))
		return (0);
	return (1);
}

int	validate_color(char *color, char *name, char *type)
{
	if (!color)
	{
		printf("Error: Missing %s (%s) color\n", name, type);
		return (0);
	}
	if (!validate_color_format(color))
	{
		printf("Error: Invalid %s color format: %s\n", type, color);
		return (0);
	}
	return (1);
}

int	validate_all_colors(t_map *map)
{
	int	valid;

	valid = 1;
	if (!validate_color(map->floor_color, "F", "Floor"))
		valid = 0;
	if (!validate_color(map->ceiling_color, "C", "Ceiling"))
		valid = 0;
	return (valid);
}
