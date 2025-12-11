/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/11 17:59:32 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->pixels)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->pixels + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	color_pack(t_rgba c)
{
	if (c.r < 0)
		c.r = 0;
	if (c.r > 255)
		c.r = 255;
	if (c.g < 0)
		c.g = 0;
	if (c.g > 255)
		c.g = 255;
	if (c.b < 0)
		c.b = 0;
	if (c.b > 255)
		c.b = 255;
	return ((c.r << 16) | (c.g << 8) | c.b);
}

int	clamp_tex_x(const t_img *tex, int tex_x)
{
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}
