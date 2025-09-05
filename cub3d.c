/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:40:21 by ael-azha          #+#    #+#             */
/*   Updated: 2025/08/26 17:36:57 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int 	dx;
	int		dy;
	float	step;
	float	stepX;
	float	stepY;
	float	x;
	float	y;
	int		i;
	
	dx = x1 - x0;
	dy = y1 - y0;
	step = imax(iabs(dx), iabs(dy));
	if (step == 0)
	{
		my_mlx_pixel_put(img, x0, y0, color);
		return ;
	}
	stepX = (float)dx / (float)step;
	stepY = (float)dy / (float)step;
	x = (float)x0;
	y = (float)y0;
	i = 0;
	while (i < step)
	{
		my_mlx_pixel_put(img, my_round(x), my_round(y), color);
		x += stepX;
		y += stepY;
		i++;
	}
}

int main()
{
	t_vars	vars;
	t_data	img;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "game");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, NULL);
	
	mlx_hook(vars.win, 2, 1L<<0, mlx_close, &vars);
	mlx_hook(vars.win, 17, 0, handle_destroy, &vars);
	mlx_loop(vars.mlx);
}
