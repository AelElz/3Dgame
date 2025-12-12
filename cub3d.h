/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:06:19 by ael-azha          #+#    #+#             */
/*   Updated: 2025/11/23 22:21:53 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define WIDTH	1280
#define HEIGHT	720

#define RED     0x00FF0000
#define GREEN   0x0000FF00
#define BLUE    0x000000FF
#define GRAY    0x00404040
#define CEILCLR 0x0099CCFF  // light sky
#define FLRCLR  0x00333333  // dark floor

// #include "src/get_next_line/get_next_line.h"
#include "includes/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>

#if defined(__APPLE__)
  #include "mlx/mlx.h"
  #define COLLIDE_PIX 3
  #define TILE_PX	64
  #define K_ESC		53
  #define K_W		13
  #define K_A		0
  #define K_S		1
  #define K_D		2
  #define K_LEFT	123
  #define K_RIGHT	124
  #define PI		3.14159265358979323846
  #define MLX_LOOP_END(mlx_ptr) mlx_loop_end(mlx_ptr)

#elif defined(__linux__)
  #include "mlx.h"
  #include <X11/keysym.h>
  #define K_ESC    XK_Escape
  #define K_W      XK_w
  #define K_A      XK_a
  #define K_S      XK_s
  #define K_D      XK_d
  #define K_LEFT   XK_Left
  #define K_RIGHT  XK_Right
  #define PI		3.14159265358979323846
  #define MLX_LOOP_END(mlx_ptr) ((void)0)
#else
  #error "Unsupported platform: need __APPLE__ or __linux__"
#endif

# define WIN_W  1024/2
# define WIN_H  768/2
# define FOV_DEG 60.0
# define TEX_W 64
# define TEX_H 64


typedef struct s_vec2d
{
	double x;
	double y; 
}	t_vec2d;

typedef struct s_ind2
{
	int x;
	int y;
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
	void   *img;
	char   *pixels;
	int     bpp;
	int     line_len;
	int     endian;
	int     width;
	int     height;
}			t_img;

//NO/SO/WE/EA
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
}			t_texset;

typedef struct s_map 
{
	char	**grid;
	int		width;
	int		height;
	t_rgba	top_col;
	t_rgba	floor_col;
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	t_ind2	spawn;
	char	spawn_dir;
}			t_map;

/* player position */
typedef struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
	double	move_spd;
	double	rot_spd;
}			t_player;

typedef struct s_ray
{
	t_vec2d	dir;
	t_ind2	map;
	t_vec2d	side_dist;
	t_vec2d	delta_dist;
	double	perp_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}			t_ray;

/* user input */
typedef struct s_input
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}		t_input;

/* hadi hia li 3liha kolchi */
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
}				t_game;

/*---------------------------------parsing---------------------------------*/
char		*get_next_line(int fd);


/*---------------------------------init---------------------------------*/
int		init_mlx(t_game *game);
void	init_hooks(t_game *game);
int		game_init(t_game *game, const char *cub_path);

void	set_defaults_if_empty(t_game *game);

void	game_free(t_game *game);
int		game_run(t_game *game);

void	copy_rows_to_map(t_game *g, char **rows, int h);
void	find_spawn(t_game *g);
void	build_fallback_map(t_game *g);

void	set_spawn_dir_values(t_player *p, char dir);
void	set_player_spawn(t_game *game);
/*---------------------------------init---------------------------------*/




//textures / images
int		img_new(t_game *app, t_img *dst, int width, int height);
void	img_free(t_game *app, t_img *img);

//engine init / shutdown
int		game_init(t_game *app, const char *cub_path);
void	game_free(t_game *app);
int		game_run(t_game *app);

//events / hooks
int		mlx_loop_end(void *mlx_ptr);
int		key_down(int key, t_game *app);
int		key_up(int key, t_game *app);
int		win_close(t_game *app);
int		loop_hook(t_game *app);

int		map_is_wall(const t_map *m, int mx, int my);
void	try_move(t_game *game, double new_x, double new_y);
void	move_fwd(t_game *app, double amt);
void	move_back(t_game *app, double amt);
void	move_left(t_game *app, double amt);
void	move_right(t_game *app, double amt);
void	turn_left(t_game *app, double ang);
void	turn_right(t_game *app, double ang);

//raycasting
void		cam_make_plane(t_player *p, double fov_deg);
void		ray_init(t_ray *r, const t_player *p, int screen_x);
void		ray_step_setup(t_ray *r, const t_player *p);
void		ray_dda(t_ray *r, const t_map *m);
void		ray_perp_dist(t_ray *r, const t_player *p);
const t_img	*ray_choose_tex(const t_texset *tx, const t_ray *r);

/*---------------------------------Rendering---------------------------------*/
//Draw

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	render_frame(t_game *app);
void	draw_floor_ceil(t_game *app);
void	draw_wall(t_game *app, int x, int top, int bot,
                const t_img *tex, int tex_x, int side);

//Draw Helper
void	compute_line_bounds(t_game *game, t_ray *r,
			int *top, int *bot);
double  compute_wall_x(t_game *game, t_ray *r);
int		compute_tex_x(const t_img *tex, t_ray *r, double wall_x);
void	render_column(t_game *game, int x, t_ray *r, int top, int bot);
int		color_pack(t_rgba c);

//Draw_Wall
void    		draw_wall_solid(t_game *g, int x, int top, int bot);
int				clamp_tex_x(const t_img *tex, int tex_x);
void			draw_wall_tex(t_game *g, int x, int top, int bot, const t_img *tex,
				int tex_x);
void			draw_wall(t_game *g, int x, int top, int bot,
				const t_img *tex, int tex_x, int side);
void			draw_floor_ceil(t_game *g);
unsigned int	tex_get_pixel(const t_img *tex, int tx, int ty);
int				tex_sample_scaled_y(int y, int top, int bot, int tex_h);

/*---------------------------------Rendering---------------------------------*/

#endif

