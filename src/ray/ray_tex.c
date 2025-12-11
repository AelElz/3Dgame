/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:04:45 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 22:07:32 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

const t_img	*ray_choose_tex(const t_texset *tx, const t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0.0)
			return (&tx->we);
		return (&tx->ea);
	}
	if (ray->dir.y > 0.0)
		return (&tx->no);
	return (&tx->so);
}
