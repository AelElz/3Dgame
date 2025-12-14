/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:43:49 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/14 14:46:38 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_rgba	parse_rgb_string(char *str)
{
	t_rgba	color;
	int		values[3];
	int		i;
	char	*ptr;

	i = 0;
	ptr = str;
	while (i < 3 && ptr)
	{
		values[i] = ft_atoi(ptr);
		if (values[i] < 0 || values[i] > 255)
			values[i] = 0;
		while (*ptr && *ptr != ',')
			ptr++;
		if (*ptr == ',')
			ptr++;
		i++;
	}
	color.r = values[0];
	color.g = values[1];
	color.b = values[2];
	color.a = 0;
	return (color);
}

static int	load_texture(t_game *game, t_img *tex, char *path)
{
	int	w;
	int	h;

	if (!path)
		return (0);
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!tex->img)
	{
		printf("Error: Failed to load texture: %s\n", path);
		return (0);
	}
	tex->pixels = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	tex->width = w;
	tex->height = h;
	return (1);
}

void	load_textures(t_game *game)
{
	game->tex.loaded_no = load_texture(game, &game->tex.no, game->map.no_texture);
	game->tex.loaded_so = load_texture(game, &game->tex.so, game->map.so_texture);
	game->tex.loaded_we = load_texture(game, &game->tex.we, game->map.we_texture);
	game->tex.loaded_ea = load_texture(game, &game->tex.ea, game->map.ea_texture);
}

void	parse_colors(t_game *game)
{
	if (game->map.ceiling_color)
		game->map.top_col = parse_rgb_string(game->map.ceiling_color);
	if (game->map.floor_color)
		game->map.floor_col = parse_rgb_string(game->map.floor_color);
}

void	set_defaults_if_empty(t_game *game)
{
	int	*tc;
	int	*fc;

	parse_colors(game);
	tc = (int *)&game->map.top_col;
	fc = (int *)&game->map.floor_col;
	if (*tc == 0 && *fc == 0)
	{
		game->map.top_col = (t_rgba){153, 204, 255, 0};
		game->map.floor_col = (t_rgba){51, 51, 51, 0};
	}
}
