/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/01 18:08:24 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->pixels + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	color_pack(t_rgba color)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	if (a < 0)
		a = 0;
	if (a > 255)
		a = 255;
	return ((r << 16)| (g << 8) | b);
}
unsigned int tex_get_pixel(const t_img *tex, int tx, int ty)
{
	char           *ptr;
	unsigned int    c;

	if (!tex || !tex->pixels || tx < 0 || ty < 0 || tx >= tex->width || ty >= tex->height)
		return 0;
	ptr = tex->pixels + (ty * tex->line_len + tx * (tex->bpp / 8));
	c = *(unsigned int *)ptr;
	/* Many MLX builds store ARGB; drop alpha so it shows correctly. */
	return (c & 0x00FFFFFF);
}
int tex_sample_y(int y, int top, int bot)
{
	int denom;
	int pos;
	int tex_y;

	denom = bot - top + 1;
	if (denom <= 0)
		return 0;
	pos = y - top;                 /* 0 .. denom-1 */
	tex_y = (pos * TEX_H) / denom; /* integer scale to texture height */
	if (tex_y < 0) tex_y = 0;
	if (tex_y >= TEX_H) tex_y = TEX_H - 1;
	return tex_y;
}
void draw_wall(t_game *app, int x, int top, int bot, const t_img *tex, int tex_x, int side)
{
	int y;
	int yy;
	int tex_y;
	unsigned int col;

	/* Clamp vertical span to frame bounds */
	if (top < 0) top = 0;
	if (bot >= app->frame.height) bot = app->frame.height - 1;

	/* Safety: if no texture, just draw a solid gray */
	if (!tex || !tex->pixels)
	{
		yy = top;
		while (yy <= bot)
		{
			my_mlx_pixel_put(&app->frame, x, yy, 0x888888);
			yy++;
		}
		return;
	}

	/* Clamp tex_x to texture width */
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= tex->width) tex_x = tex->width - 1;

	y = top;
	while (y <= bot)
	{
		tex_y = tex_sample_y(y, top, bot);
		/* If your textures are not exactly TEX_H wide/high, scale here */
		if (TEX_H != tex->height)
			tex_y = (tex_y * tex->height) / TEX_H;
		if (tex_x >= tex->width) /* recheck in case of scaling differences */
			tex_x = tex->width - 1;

		col = tex_get_pixel(tex, tex_x, tex_y);

		/* simple side shading (optional): darken y-sides a bit */
		if (side == 1)
		{
			int r = (col >> 16) & 0xFF;
			int g = (col >> 8)  & 0xFF;
			int b =  col        & 0xFF;
			r = (r * 70) / 100;
			g = (g * 70) / 100;
			b = (b * 70) / 100;
			col = (unsigned int)((r << 16) | (g << 8) | b);
		}
		my_mlx_pixel_put(&app->frame, x, y, (int)col);
		y++;
	}
}

/* small helper to draw one vertical line */
void	draw_vline(t_img *img, int x, int y0, int y1, int color)
{
	int y;

	if (y0 < 0)
		y0 = 0;
	if (y1 >= img->height)
		y1 = img->height - 1;
	y = y0;
	while (y <= y1)
	{
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
}
void    draw_floor_ceil(t_game *app)
{
    int y;
    int x;
    int ceilc;
    int floorc;

    ceilc  = color_pack(app->map.top_col);
    floorc = color_pack(app->map.floor_col);

    y = 0;
    while (y < app->frame.height)
    {
        x = 0;
        while (x < app->frame.width)
        {
            if (y < app->frame.height / 2)
                my_mlx_pixel_put(&app->frame, x, y, ceilc);
            else
                my_mlx_pixel_put(&app->frame, x, y, floorc);
            x++;
        }
        y++;
    }
}

/* optional tiny darken (fixed 70%) for side==1 */
int	darken_70(int c)
{
	int r = (c >> 16) & 0xFF;
	int g = (c >>  8) & 0xFF;
	int b =  c        & 0xFF;

	r = (r * 70) / 100;
	g = (g * 70) / 100;
	b = (b * 70) / 100;
	return ((r << 16) | (g << 8) | b);
}

void	render_frame(t_game *game)
{
	int		y;
	int		x;
	int		ceilc;
	int		floorc;

	/* 1) sky / floor fill */
	ceilc  = color_pack(game->map.top_col);   /* was top_col -> ceil_col */
	floorc = color_pack(game->map.floor_col);

	y = 0;
	while (y < game->frame.height)
	{
		x = 0;
		while (x < game->frame.width)
		{
			if (y < game->frame.height / 2)
				my_mlx_pixel_put(&game->frame, x, y, ceilc);
			else
				my_mlx_pixel_put(&game->frame, x, y, floorc);
			x++;
		}
		y++;
	}

	draw_floor_ceil(game);

	x = 0;
	while (x < game->frame.width)
	{
    	t_ray r;
    	int line_h, top, bot;
    	const t_img *tex;
    	int tex_x;

    	ray_init(&r, &game->player, x);
    	ray_step_setup(&r, &game->player);
    	ray_dda(&r, &game->map);
    	ray_perp_dist(&r, &game->player);

    	line_h = (int)((double)game->frame.height / r.perp_dist);
    	top = game->frame.height/2 - line_h/2;
    	bot = top + line_h - 1;

    /* compute wall hit x for tex_x (simple version) */
    	{
        	double wall_x;
        	if (r.side == 0)
        		wall_x = game->player.pos.y + r.perp_dist * r.dir.y;
        	else
            	wall_x = game->player.pos.x + r.perp_dist * r.dir.x;
        	wall_x -= floor(wall_x);
        	tex = ray_choose_tex(&game->tex, &r);
        	tex_x = (int)(wall_x * (double)tex->width);
        	if ((r.side == 0 && r.dir.x > 0) || (r.side == 1 && r.dir.y < 0))
            	tex_x = tex->width - 1 - tex_x; /* mirror to keep continuity */
    	}
    	draw_wall(game, x, top, bot, tex, tex_x, r.side);
    	x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
