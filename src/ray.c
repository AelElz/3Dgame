/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:15:51 by ayoub             #+#    #+#             */
/*   Updated: 2025/09/18 14:29:00 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    cam_make_plane(t_player *player, double fov_deg)
{
	double	half;
	double	tangent;

	half = (fov_deg * PI / 180.0) * 0.5;
	tangent = (tan(half));

	player->plane.x = -player->dir.y * tangent;
	player->plane.y = player->dir.x * tangent;
}
