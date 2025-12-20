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
	// if (result < 0 || result > 255)
	// 	return (-1);
	return (result * sign);
}

void	extract_colors(t_game *game, char *colors_str)
{
	int	i;
	char	**colors;
	int	c;
	int	com;

	com = 0;
	i = 0;
	while (colors_str[i])
	{
		if (colors_str[i] == ',')
			com++;
		if (!((colors_str[i] >= '0' && colors_str[i] <= '9') || colors_str[i] == ',') || com > 2)
			exiting("Error: invalid colors value\n", game);
		i++;
	}
	colors = ft_split_colors(colors_str);
	i = 0;
	while (colors[i])
	{
		c = ft_atoi(colors[i]);
		if ((i == 2 && colors[i + 1] != NULL) || !(c >= 0 && c <= 255))
			exiting("Error: invalid colors value\n", game);
		i++;
	}
	freeing_arr(colors);
}

int	extract_texture(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exiting("Error: invalid texture file\n", game);
	close (fd);
	return (1);
}

void    parse_key_value(t_game *game)
{
	extract_colors(game, game->p->elements_splited.c[1]);
	game->map.ceiling_color = game->p->elements_splited.c[1];
	game->map.floor_color = game->p->elements_splited.f[1];
	if (extract_texture(game, game->p->elements_splited.no[1]))
		game->map.no_texture = game->p->elements_splited.no[1];
	if (extract_texture(game, game->p->elements_splited.so[1]))
		game->map.so_texture = game->p->elements_splited.so[1];
	if (extract_texture(game, game->p->elements_splited.we[1]))
		game->map.we_texture = game->p->elements_splited.we[1];
	if (extract_texture(game, game->p->elements_splited.ea[1]))
		game->map.ea_texture = game->p->elements_splited.ea[1];	
}

int skip_empty(char *str)
{
        int i;

        i = 0;
        while (str[i] == ' ' || str[i] == '\t')
                i++;
        return (i);
}


void    parse_first_elements(t_game *game)
{
	int i;
	i = 0;
	while (game->p->first_six[i])
	{
		if (ft_strcmp(game->p->first_six[i] + skip_empty(game->p->first_six[i]), "F") && !game->p->elements_splited.f)
			game->p->elements_splited.f = ft_split_idinfo(game->p->first_six[i]);
		else if (ft_strcmp(game->p->first_six[i] + skip_empty(game->p->first_six[i]), "C") && !game->p->elements_splited.c)
			game->p->elements_splited.c = ft_split_idinfo(game->p->first_six[i]);
		else if (ft_strcmp(game->p->first_six[i] + skip_empty(game->p->first_six[i]), "NO") && !game->p->elements_splited.no)
			game->p->elements_splited.no = ft_split_idinfo(game->p->first_six[i]);
		else if (ft_strcmp(game->p->first_six[i] + skip_empty(game->p->first_six[i]), "SO") && !game->p->elements_splited.so)
			game->p->elements_splited.so = ft_split_idinfo(game->p->first_six[i]);
		else if (ft_strcmp(game->p->first_six[i] + skip_empty(game->p->first_six[i]), "WE") && !game->p->elements_splited.we)
			game->p->elements_splited.we = ft_split_idinfo(game->p->first_six[i]);
		else if (ft_strcmp(game->p->first_six[i] + skip_empty(game->p->first_six[i]), "EA") && !game->p->elements_splited.ea)
			game->p->elements_splited.ea = ft_split_idinfo(game->p->first_six[i]);
		else
			exiting("Error: Invalid elements\n", game);
		i++;
	}
}
