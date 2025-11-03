/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:15:51 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/03 20:34:07 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    cam_make_plane(t_player *player, double fov_deg)
{
	double half = (fov_deg * PI / 180.0) * 0.5;
	double tangent = tan(half);

	player->plane.x = -player->dir.y * tangent;
	player->plane.y =  player->dir.x * tangent;
}

void	ray_init(t_ray *r, const t_player *p, int screen_x)
{
	double camX;

	r->hit  = 0;
	r->side = 0;

	camX = 2.0 * (double)screen_x / (double)(WIN_W - 1) - 1.0;

	r->dir.x = p->dir.x + p->plane.x * camX;
	r->dir.y = p->dir.y + p->plane.y * camX;

	r->map.x = (int)p->pos.x;
	r->map.y = (int)p->pos.y;

	r->delta_dist.x = (r->dir.x == 0.0) ? 1e30 : fabs(1.0 / r->dir.x);
	r->delta_dist.y = (r->dir.y == 0.0) ? 1e30 : fabs(1.0 / r->dir.y);
}

void	ray_step_setup(t_ray *r, const t_player *p)
{
	if (r->dir.x < 0.0)
	{
		r->step_x = -1;
		r->side_dist.x = (p->pos.x - (double)r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist.x = ((double)r->map.x + 1.0 - p->pos.x) * r->delta_dist.x;
	}
	if (r->dir.y < 0.0)
	{
		r->step_y = -1;
		r->side_dist.y = (p->pos.y - (double)r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist.y = ((double)r->map.y + 1.0 - p->pos.y) * r->delta_dist.y;
	}
}

void	ray_dda(t_ray *r, const t_map *m)
{
	int safety = 0;
	const int SAFETY_MAX = 100000;

	while (r->hit == 0 && safety++ < SAFETY_MAX)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step_y;
			r->side = 1;
		}
		if (r->map.x < 0 || r->map.y < 0 || r->map.y >= m->height || r->map.x >= m->width)
		{
			r->hit = 1;
			break;
		}
		if (!m->grid || !m->grid[r->map.y])
		{
			r->hit = 1;
			break;
		}
		{
			char c = m->grid[r->map.y][r->map.x];
			if (c == '1' || c == ' ')
			{
				r->hit = 1;
				break;
			}
		}
	}
}

void	ray_perp_dist(t_ray *r, const t_player *p)
{
	if (r->side == 0)
		r->perp_dist = ((double)r->map.x - p->pos.x + (1.0 - (double)r->step_x) * 0.5) / r->dir.x;
	else
		r->perp_dist = ((double)r->map.y - p->pos.y + (1.0 - (double)r->step_y) * 0.5) / r->dir.y;

	if (r->perp_dist < 1e-6)
		r->perp_dist = 1e-6;
}

/* Choose texture based on which face we hit and ray direction.
   side == 0 means a vertical grid line (we moved along x), so the face is E/W.
   side == 1 means a horizontal grid line (we moved along y), so the face is N/S. */
const t_img	*ray_choose_tex(const t_texset *tx, const t_ray *r)
{
	if (r->side == 0)
	{
		/* we crossed a vertical boundary: the wall we see faces West if dir.x > 0 (we came from West),
		   and faces East if dir.x < 0 (we came from East). */
		return (r->dir.x > 0.0) ? &tx->we : &tx->ea;
	}
	/* crossed horizontal boundary: the wall faces North if dir.y > 0, else South */
	return (r->dir.y > 0.0) ? &tx->no : &tx->so;
}
