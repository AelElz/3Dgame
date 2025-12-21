/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:05:18 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/11 17:58:43 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cam_make_plane(t_player *player, double fov_deg)
{
	double	half;
	double	tangent;

	half = (fov_deg * PI / 180.0) * 0.5;
	tangent = tan(half);
	player->plane.x = -player->dir.y * tangent;
	player->plane.y = player->dir.x * tangent;
}
