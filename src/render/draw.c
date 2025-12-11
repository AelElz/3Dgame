/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 21:33:35 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	tex_get_pixel(const t_img *tex, int tx, int ty)
{
	char			*ptr;
	unsigned int	c;

	if (!tex || !tex->pixels || tx < 0 || ty < 0
		|| tx >= tex->width || ty >= tex->height)
		return (0);
	ptr = tex->pixels + (ty * tex->line_len + tx * (tex->bpp / 8));
	c = *(const unsigned int *)ptr;
	return (c & 0x00FFFFFF);
}

int	tex_sample_scaled_y(int y, int top, int bot, int tex_h)
{
	int	denom;
	int	pos;
	int	ty;

	denom = bot - top + 1;
	pos = y - top;
	if (denom <= 0)
		return (0);
	ty = (pos * tex_h) / denom;
	if (ty < 0)
		ty = 0;
	if (ty >= tex_h)
		ty = tex_h - 1;
	return (ty);
}
void	draw_floor_ceil(t_game *g)
{
	int	ceilc;
	int	floorc;
	int	y;
	int	x;
	int	half;

	ceilc = color_pack(g->map.top_col);
	floorc = color_pack(g->map.floor_col);
	half = g->frame.height / 2;
	y = 0;
	while (y < g->frame.height)
	{
		x = 0;
		while (x < g->frame.width)
		{
			if (y < half)
				my_mlx_pixel_put(&g->frame, x, y, ceilc);
			else
				my_mlx_pixel_put(&g->frame, x, y, floorc);
			x++;
		}
		y++;
	}
}

void	render_frame(t_game *game)
{
	int	x;
	t_ray	r;
	int	top;
	int	bot;

	draw_floor_ceil(game);
	x = 0;
	while (x < game->frame.width)
	{
		ray_init(&r, &game->player, x);
		ray_step_setup(&r, &game->player);
		ray_dda(&r, &game->map);
		ray_perp_dist(&r, &game->player);
		compute_line_bounds(game, &r, &top, &bot);
		render_column(game, x, &r, top, bot);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
