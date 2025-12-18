#include "parsing.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += (nptr[i++] - 48);
	}
	return (result * sign);
}

int	extract_colors(t_parsing *p, char *colors_str)
{
	int	i;
	char	**colors;
	int	c;
	int	ret;

	i = 0;
	ret = -1;
	while (colors_str[i])
	{
		if (!((colors_str[i] >= '0' && colors_str[i] <= '9') || colors_str[i] == ','))
			exiting("Error: invalid colors value\n", p);
		i++;
	}
	colors = ft_split_colors(colors_str);
	i = 0;
	while (colors[i])
	{
		c = ft_atoi(colors[i]);
		if ((i == 2 && colors[i + 1] != NULL) || !(c >= 0 && c <= 255))
			exiting("Error: invalid colors value\n", p);
		ret = (ret << 8) + c;
		i++;
	}
	freeing_arr(colors);
	printf("%d\n", ret);
	return (ret);
}

char	*extract_texture(t_parsing *p, char *tex)
{
	int	fd;

	fd = open(tex, O_RDONLY);
	if (fd < 0)
		exiting("Error: invalid texture file\n", p);
	return (tex);
}

void    parse_key_value(t_parsing *p)
{
	p->f_rgb = -1;
	p->f_rgb = -1;
	// p->f_rgb = extract_colors(p, p->elements_splited.f[1]);
	// p->c_rgb = extract_colors(p, p->elements_splited.f[1]);
	// printf("%s", p->elements_splited.f[1]);
	// printf("%s", p->elements_splited.c[1]);
	// p->no_tex = extract_texture(p, p->elements_splited.no[1]);
	// printf("%s", p->elements_splited.no[1]);
}

void    parse_first_elements(t_parsing *p)
{
	int i;
	i = 0;
	while (p->first_six[i])
	{
		if (ft_strcmp(p->first_six[i], "F") && !p->elements_splited.f)
			p->elements_splited.f = ft_split_idinfo(p->first_six[i]);
		else if (ft_strcmp(p->first_six[i], "C") && !p->elements_splited.c)
			p->elements_splited.c = ft_split_idinfo(p->first_six[i]);
		else if (ft_strcmp(p->first_six[i], "NO") && !p->elements_splited.no)
			p->elements_splited.no = ft_split_idinfo(p->first_six[i]);
		else if (ft_strcmp(p->first_six[i], "SO") && !p->elements_splited.so)
			p->elements_splited.so = ft_split_idinfo(p->first_six[i]);
		else if (ft_strcmp(p->first_six[i], "WE") && !p->elements_splited.we)
			p->elements_splited.we = ft_split_idinfo(p->first_six[i]);
		else if (ft_strcmp(p->first_six[i], "EA") && !p->elements_splited.ea)
			p->elements_splited.ea = ft_split_idinfo(p->first_six[i]);
		else
			exiting("Error: Invalid elements\n", p);
		i++;
	}
}