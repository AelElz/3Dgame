/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:06:19 by ael-azha          #+#    #+#             */
/*   Updated: 2025/08/26 17:36:11 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define WIDTH	1280
#define HEIGHT	720

#include "includes/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>

typedef struct	s_data
{
	void	*img;
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	int		x;
	t_data	frame;
}			t_vars;

// Math
int	iabs(int v);
int	imax(int a, int b);
int	my_round(float x);

// Clear
int		handle_destroy(t_vars *vars);
int		mlx_close(int keycode, t_vars *vars);
void	clear_image(t_data *img, int color);

//Render
void	draw_line(t_data *img, int x0, int y0, int x1, int y1, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, t_vars *vars);
int		mouse_hook(int button, int x, int y, void *param);

#endif

