/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:27:59 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 21:33:41 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->pixels)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->pixels + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	color_pack(t_rgba c)
{
	if (c.r < 0)
		c.r = 0;
	if (c.r > 255)
		c.r = 255;
	if (c.g < 0)
		c.g = 0;
	if (c.g > 255)
		c.g = 255;
	if (c.b < 0)
		c.b = 0;
	if (c.b > 255)
		c.b = 255;
	return ((c.r << 16) | (c.g << 8) | c.b);
}

void    draw_wall_solid(t_game *g, int x, int top, int bot)
{
	int	y;

	if (top < 0)
		top = 0;
	if (bot >= g->frame.height)
		bot = g->frame.height - 1;
	y = top;
	while (y <= bot)
	{
		my_mlx_pixel_put(&g->frame, x, y, 0x808080);
		y++;
	}
}

int clamp_tex_x(const t_img *tex, int tex_x)
{
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

void	draw_wall_tex(t_game *g, int x, int top, int bot, const t_img *tex,
		int tex_x)
{
	int				y;
	int				ty;
	unsigned int	col;

	if (top < 0)
		top = 0;
	if (bot >= g->frame.height)
		bot = g->frame.height - 1;
	tex_x = clamp_tex_x(tex, tex_x);
	y = top;
	while (y <= bot)
	{
		ty = tex_sample_scaled_y(y, top, bot, tex->height);
		col = tex_get_pixel(tex, tex_x, ty);
		my_mlx_pixel_put(&g->frame, x, y, (int)col);
		y++;
	}
}

void	draw_wall(t_game *g, int x, int top, int bot,
			const t_img *tex, int tex_x, int side)
{
	(void)side;
	if (!tex || !tex->pixels)
		draw_wall_solid(g, x, top, bot);
	else
		draw_wall_tex(g, x, top, bot, tex, tex_x);
}
