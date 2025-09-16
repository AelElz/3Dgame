/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/09/16 15:26:12 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->wight || y >= img->height)
		return ;
	dst = img->pixels + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	color_pack(t_rgba color)
{
	int	r;
	int	g;
	int	b;

	r = color.r;
	g = color.g;
	b = color.b;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16)| (g << 8) | b);
}

void	draw_frame(t_game *game)
{
	int	x;
	int	y;
	int	top;
	int	floor;

	top = color_pack(game->map.top_col);
	floor = color_pack(game->map.floor_col);
	y = 0;
	while (y < game->frame.height)
	{
		x = 0;
		while (x < game->frame.wight)
		{
			if (y < game->frame.height / 2)
				my_mlx_pixel_put(&game, x, y, top);
			else
				my_mlx_pixel_put(&game, x, y, floor);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
