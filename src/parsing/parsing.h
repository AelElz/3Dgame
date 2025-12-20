#include "gnl/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "../../cub3d.h"
// typedef struct s_elements_splited
// {
// 	char **f;
// 	char **c;
// 	char **no;
// 	char **so;
// 	char **we;
// 	char **ea;
// } t_elements_splited;

// typedef struct s_player_info
// {
// 	double	player_x;
// 	double	player_y;
// 	double	angle;
// }	t_player_info;

// typedef struct s_map
// {
// 	char			**grid;
// 	char			**map;//
// 	// char			**map_full;
// 	int				width;
// 	int				height;
// 	// t_rgba			top_col;
// 	// t_rgba			floor_col;
// 	// char			*tex_no;
// 	// char			*tex_so;
// 	// char			*tex_we;
// 	// char			*tex_ea;
// 	char			*no_texture;
// 	char			*so_texture;
// 	char			*we_texture;
// 	char			*ea_texture;
// 	// t_img			north_tex;
// 	// t_img			south_tex;
// 	// t_img			west_tex;
// 	// t_img			east_tex;
// 	// t_img			img;
// 	// void			*mlx;
// 	// void			*win;
// 	// t_ind2			spawn;
// 	char			spawn_dir;
// 	char			*floor_color;
// 	char			*ceiling_color;
// 	t_player_info	player;
// 	int				player_set;
// }	t_map;

// typedef struct s_parsing
// {
// 	char	            **file;
// 	char	            **first_six;
// 	int                 has_map;
// 	t_map				map;
// 	t_elements_splited  elements_splited;
// } t_parsing;

// typedef struct s_parsing
// {
// 	char	            **file;
// 	char	            **first_six;
// 	char                **map;
// 	int                 has_map;
// 	int					f_rgb;
// 	int					c_rgb;
// 	char				*no_tex;
// 	char				*so_tex;
// 	char				*we_tex;
// 	char				*ea_tex;
// 	t_elements_splited  elements_splited;
// } t_parsing;

// // main.c
// int     ft_strcmp(char *s1, char *s2);
// int     check_the_file_extension(char *file);

// // parsing.c
// int     parse_first_six(t_parsing *p);
// void    parse_map(t_parsing *p, int i);
// void    parse_file(t_parsing *p);
// void	init_elements_splited(t_elements_splited *elements_splited);
// void	main_parsing(t_parsing *p);

// // parsing2.c
// void    freeing_arr(char **arr);
// void    exiting(char *msg, t_parsing *p);
// void    remove_newline(char *str);
// int     is_empty(char *str);
// int     contain_two_parts(char *str);

// // parsing3.c
// void    parse_key_value(t_parsing *p);
// void    parse_first_elements(t_parsing *p);

// // reading.c
// int     count_lines(char *file);
// char    **read_file(char *file);

// //split.c
// char	**ft_split_colors(char const *s);
// char	**ft_split_idinfo(char const *s);