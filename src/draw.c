/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/04 14:28:55 by ayoub            ###   ########.fr       */
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
	if (c.r < 0) c.r = 0; if (c.r > 255) c.r = 255;
	if (c.g < 0) c.g = 0; if (c.g > 255) c.g = 255;
	if (c.b < 0) c.b = 0; if (c.b > 255) c.b = 255;
	return ((c.r << 16) | (c.g << 8) | c.b);
}

unsigned int	tex_get_pixel(const t_img *tex, int tx, int ty)
{
	const char *ptr;
	unsigned int c;

	if (!tex || !tex->pixels || tx < 0 || ty < 0
		|| tx >= tex->width || ty >= tex->height)
		return 0;
	ptr = tex->pixels + (ty * tex->line_len + tx * (tex->bpp / 8));
	c = *(const unsigned int *)ptr;
	return (c & 0x00FFFFFF);
}

int	tex_sample_scaled_y(int y, int top, int bot, int tex_h)
{
	int	denom = bot - top + 1;
	int	pos = y - top;
	int	ty;

	if (denom <= 0)
		return (0);
	ty = (pos * tex_h) / denom;
	if (ty < 0)
		ty = 0;
	if (ty >= tex_h)
		ty = tex_h - 1;
	return (ty);
}

void	draw_wall(t_game *g, int x, int top, int bot,
			   const t_img *tex, int tex_x, int side)
{
	int	y;

	if (top < 0)
		top = 0;
	if (bot >= g->frame.height)
		bot = g->frame.height - 1;
	if (!tex || !tex->pixels)
	{
		for (y = top; y <= bot; ++y) my_mlx_pixel_put(&g->frame, x, y, 0x808080);
		return;
	}
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	for (y = top; y <= bot; ++y)
	{
		int ty = tex_sample_scaled_y(y, top, bot, tex->height);
		unsigned int col = tex_get_pixel(tex, tex_x, ty);

		if (side == 1)
		{
			int r = (col >> 16) & 0xFF, gch = (col >> 8) & 0xFF, b = col & 0xFF;
			r = (r * 70) / 100; gch = (gch * 70) / 100; b = (b * 70) / 100;
			col = (unsigned)((r << 16) | (gch << 8) | b);
		}
		my_mlx_pixel_put(&g->frame, x, y, (int)col);
	}
}

void draw_floor_ceil(t_game *g)
{
	const int ceilc  = color_pack(g->map.top_col);
	const int floorc = color_pack(g->map.floor_col);
	int y, x, half = g->frame.height / 2;

	for (y = 0; y < g->frame.height; ++y)
	{
		const int col = (y < half) ? ceilc : floorc;
		for (x = 0; x < g->frame.width; ++x)
			my_mlx_pixel_put(&g->frame, x, y, col);
	}
}

void	render_frame(t_game *game)
{
	int x;

	draw_floor_ceil(game);
	for (x = 0; x < game->frame.width; ++x)
	{
		t_ray r;
		int line_h, top, bot;
		const t_img *tex = NULL;
		int tex_x;
		double wall_x;

		ray_init(&r, &game->player, x);
		ray_step_setup(&r, &game->player);
		ray_dda(&r, &game->map);
		ray_perp_dist(&r, &game->player);

		line_h = (int)((double)game->frame.height / r.perp_dist);
		top    = game->frame.height/2 - line_h/2;
		bot    = top + line_h - 1;

		if (r.side == 0)
			wall_x = game->player.pos.y + r.perp_dist * r.dir.y;
		else
			wall_x = game->player.pos.x + r.perp_dist * r.dir.x;
		wall_x -= floor(wall_x);

		tex = ray_choose_tex(&game->tex, &r);
		if (!tex || tex->width <= 0) {
			draw_wall(game, x, top, bot, NULL, 0, r.side);
			continue;
		}
		tex_x = (int)(wall_x * (double)tex->width);

		if ((r.side == 0 && r.dir.x > 0) || (r.side == 1 && r.dir.y < 0))
			tex_x = tex->width - 1 - tex_x;

		draw_wall(game, x, top, bot, tex, tex_x, r.side);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
