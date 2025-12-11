/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:31:25 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/11 17:59:14 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	img_new(t_game *game, t_img *dst, int width, int height)
{
	dst->img = mlx_new_image(game->mlx, width, height);
	dst->pixels = mlx_get_data_addr(dst->img, &dst->bpp, &dst->line_len,
			&dst->endian);
	dst->width = width;
	dst->height = height;
	return (0);
}

void	img_free(t_game *game, t_img *img)
{
	if (img && img->img)
		mlx_destroy_image(game->mlx, img->img);
	ft_memset(img, 0, sizeof(*img));
}
