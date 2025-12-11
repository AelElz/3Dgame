/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:31:17 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/11 18:47:15 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define GRAY 0x00404040
# define CEILCLR 0x0099CCFF
# define FLRCLR 0x00333333
# define PI 3.14159265358979323846

# include "includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <math.h>
# include "mlx.h"
# include <X11/keysym.h>
# define K_ESC XK_Escape
# define K_W XK_w
# define K_A XK_a
# define K_S XK_s
# define K_D XK_d
# define K_LEFT XK_Left
# define K_RIGHT XK_Right

# define WIN_W 1024
# define WIN_H 768
# define FOV_DEG 60.0
# define TEX_W 64
# define TEX_H 64
# define TILE 64

typedef struct s_player_info
{
	double	player_x;
	double	player_y;
	double	angle;
}	t_player_info;

typedef struct s_vec2d
{
	double	x;
	double	y;
}	t_vec2d;

typedef struct s_ind2
{
	int	x;
	int	y;
}	t_ind2;

typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgba;

typedef struct s_img
{
	void	*img;
	char	*pixels;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texset
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	bool	loaded_no;
	bool	loaded_so;
	bool	loaded_we;
	bool	loaded_ea;
}	t_texset;

typedef struct s_map
{
	char			**grid;
	char			**map;
	int				width;
	int				height;
	t_rgba			top_col;
	t_rgba			floor_col;
	char			*tex_no;
	char			*tex_so;
	char			*tex_we;
	char			*tex_ea;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	t_img			north_tex;
	t_img			south_tex;
	t_img			west_tex;
	t_img			east_tex;
	t_img			img;
	void			*mlx;
	void			*win;
	t_ind2			spawn;
	char			spawn_dir;
	char			*floor_color;
	char			*ceiling_color;
	t_player_info	player;
	int				player_set;
}	t_map;

typedef struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
	double	move_spd;
	double	rot_spd;
}	t_player;

typedef struct s_ray
{
	t_vec2d			dir;
	t_ind2			map;
	t_vec2d			side_dist;
	t_vec2d			delta_dist;
	double			perp_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				top;
	int				bot;
	const t_img		*tex;
	int				tex_x;
}	t_ray;

typedef struct s_input
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_input;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_map		map;
	t_texset	tex;
	t_player	player;
	t_input		input;
	bool		running;
}	t_game;

int				init_mlx(t_game *game);
void			init_hooks(t_game *game);
int				game_init(t_game *game, const char *cub_path);
void			set_defaults_if_empty(t_game *game);
void			game_free(t_game *game);
int				game_run(t_game *game);
void			copy_rows_to_map(t_game *g, char **rows, int h);
void			find_spawn(t_game *g);
void			build_fallback_map(t_game *g);
void			set_spawn_dir_values(t_player *p, char dir);
void			set_player_spawn(t_game *game);
int				mlx_destroy_display(void *mlx_ptr);
int				img_new(t_game *app, t_img *dst, int width, int height);
void			img_free(t_game *app, t_img *img);
int				key_down(int key, t_game *app);
int				key_up(int key, t_game *app);
int				win_close(t_game *app);
int				loop_hook(t_game *app);
int				map_is_wall(const t_map *m, int mx, int my);
void			try_move(t_game *game, double new_x, double new_y);
void			move_fwd(t_game *app, double amt);
void			move_back(t_game *app, double amt);
void			move_left(t_game *app, double amt);
void			move_right(t_game *app, double amt);
void			turn_left(t_game *app, double ang);
void			turn_right(t_game *app, double ang);
void			cam_make_plane(t_player *p, double fov_deg);
void			ray_init(t_ray *r, const t_player *p, int screen_x);
void			ray_step_setup(t_ray *r, const t_player *p);
void			ray_dda(t_ray *r, const t_map *m);
void			ray_perp_dist(t_ray *r, const t_player *p);
const t_img		*ray_choose_tex(const t_texset *tx, const t_ray *r);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			render_frame(t_game *app);
void			draw_floor_ceil(t_game *app);
void			compute_line_bounds(t_game *g, t_ray *r, int *top, int *bot);
double			compute_wall_x(t_game *game, t_ray *r);
int				compute_tex_x(const t_img *tex, t_ray *r, double wall_x);
void			render_column(t_game *game, int x, t_ray *r);
int				color_pack(t_rgba c);
void			draw_wall_solid(t_game *g, int x, int top, int bot);
int				clamp_tex_x(const t_img *tex, int tex_x);
void			draw_wall_tex(t_game *g, int x, t_ray *r);
void			draw_wall(t_game *g, int x, t_ray *r);
unsigned int	tex_get_pixel(const t_img *tex, int tx, int ty);
int				tex_sample_scaled_y(int y, int top, int bot, int tex_h);

#endif