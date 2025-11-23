/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:30:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 22:05:17 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_init(t_ray *r, const t_player *p, int screen_x)
{
	double	camX;
	
	r->hit = 0;
	r->side = 0;
	camX = 2.0 * (double)screen_x / (double)(WIN_W - 1) - 1.0;
	r->dir.x = p->dir.x + p->plane.x * camX;
	r->dir.y = p->dir.y + p->plane.y * camX;
	r->map.x = (int)floor(p->pos.x);
	r->map.y = (int)floor(p->pos.y);
	if (r->dir.x == 0.0)
		r->delta_dist.x = 1e30;
	else
		r->delta_dist.x = fabs(1.0 / r->dir.x);
	if (r->dir.y == 0.0)
		r->delta_dist.y = 1e30;
	else
		r->delta_dist.y = fabs(1.0 / r->dir.y);
}

void	ray_step_setup(t_ray *ray, const t_player *p)
{
	if (ray->dir.x < 0.0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (p->pos.x - (double)ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = ((double)ray->map.x + 1.0 - p->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0.0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (p->pos.y - (double)ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = ((double)ray->map.y + 1.0 - p->pos.y)
			* ray->delta_dist.y;
	}
}

void	ray_dda(t_ray *ray, const t_map *map)
{
	int	safety;
	int	max_steps;

	safety = -1;
	max_steps = 100000;
	while (ray->hit == 0 && ++safety < max_steps)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step_y;
			ray->side = 1;
		}
		if (map_is_wall(map, ray->map.x, ray->map.y))
		{
			ray->hit = 1;
			break ;
		}
	}
}

void	ray_perp_dist(t_ray *ray, const t_player *p)
{
	(void)p;
	if (ray->side == 0)
		ray->perp_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_dist = ray->side_dist.y - ray->delta_dist.y;
	if (ray->perp_dist < 0.0001)
		ray->perp_dist = 0.0001;
}
