/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:27:59 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/14 15:01:20 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_wall_solid(t_game *g, int x, int top, int bot)
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

void	draw_wall_tex(t_game *g, int x, t_ray *r)
{
	int				y;
	int				ty;
	unsigned int	col;
	int				start;
	int				end;

	start = r->top;
	end = r->bot;
	if (start < 0)
		start = 0;
	if (end >= g->frame.height)
		end = g->frame.height - 1;
	r->tex_x = clamp_tex_x(r->tex, r->tex_x);
	y = start;
	while (y <= end)
	{
		ty = tex_sample_scaled_y(y, r->top, r->bot, r->tex->height);
		col = tex_get_pixel(r->tex, r->tex_x, ty);
		my_mlx_pixel_put(&g->frame, x, y, (int)col);
		y++;
	}
}

void	draw_wall(t_game *g, int x, t_ray *r)
{
	if (!r->tex || !r->tex->pixels)
		draw_wall_solid(g, x, r->top, r->bot);
	else
		draw_wall_tex(g, x, r);
}
