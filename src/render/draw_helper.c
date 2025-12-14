/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:23:56 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/14 15:01:20 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	compute_line_bounds(t_game *game, t_ray *r,
			int *top, int *bot)
{
	int	line_h;

	if (r->perp_dist < 0.001)
		r->perp_dist = 0.001;
	line_h = (int)((double)game->frame.height / r->perp_dist);
	*top = (game->frame.height - line_h) / 2;
	*bot = *top + line_h;
}

double	compute_wall_x(t_game *game, t_ray *r)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = game->player.pos.y + r->perp_dist * r->dir.y;
	else
		wall_x = game->player.pos.x + r->perp_dist * r->dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	compute_tex_x(const t_img *tex, t_ray *r, double wall_x)
{
	int	tex_x;

	if (!tex || tex->width <= 0)
		return (0);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((r->side == 0 && r->dir.x > 0) || (r->side == 1 && r->dir.y < 0))
		tex_x = tex->width - 1 - tex_x;
	return (tex_x);
}

void	render_column(t_game *game, int x, t_ray *r)
{
	double		wall_x;
	int			tex_x;

	wall_x = compute_wall_x(game, r);
	r->tex = ray_choose_tex(&game->tex, r);
	if (!r->tex || r->tex->width <= 0)
	{
		draw_wall(game, x, r);
		return ;
	}
	tex_x = compute_tex_x(r->tex, r, wall_x);
	r->tex_x = tex_x;
	draw_wall(game, x, r);
}
