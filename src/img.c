/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:16:07 by ayoub             #+#    #+#             */
/*   Updated: 2025/09/18 14:37:16 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	img_new(t_game *game, t_img *dst, int width, int height)
{
	dst->img = mlx_new_image(game->mlx, width, height);
	dst->pixels = mlx_get_data_addr(dst->img, &dst->bpp, &dst->line_len,
		&dst->endian);
	dst->wight = width;
	dst->height = height;
	return (0);
}

void	img_free(t_game *game, t_img *img)
{
	if (img && img->img)
		mlx_destroy_image(game->mlx, img->img);
	ft_memset(img, 0, sizeof(*img));
}
