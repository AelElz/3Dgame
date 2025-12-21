/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:22:51 by aboukent          #+#    #+#             */
/*   Updated: 2025/12/21 22:54:43 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../cub3d.h"
# include <fcntl.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_flood_data
{
	t_point	*stack;
	char	**visited;
	int		*stack_size;
}	t_flood_data;

// parse_map_closed1.c
void	add_neighbor_to_stack(t_flood_data *data, t_point neighbor, t_map *map);
int		check_boundary_escape(t_map *map, int nx, int ny);
void	init_directions(int *dx, int *dy);
int		process_neighbors(t_map *map, t_point p, t_flood_data *data);
int		flood_fill_loop(t_map *map, t_flood_data *data);

// parse_map_closed.c
void	free_visited(char **visited, t_map *map);
t_point	*allocate_stack(t_map *map, char **visited);
char	**allocate_visited(t_map *map);
int		check_map_closed(t_map *map, int start_x, int start_y);
int		validate_and_set_player(t_map *map);

// parse_player.c
void	set_player_angle(t_map *map, char c);
void	process_player_found(t_map *map, int x, int y, int *pc);
void	scan_map_for_player(t_map *map, int *pc, int *px, int *py);

// parse_spaces.c
void	convert_line_spaces(char *line, int first, int last);
void	find_space_bounds(char *line, int len, int *first, int *last);
void	convert_spaces_to_floor(t_map *map);

// parse_validate_map1.c
int		find_last_nonspace(char *row, int len);
int		find_first_nonspace(char *row, int len);
int		check_row_borders(t_map *map, int y, int first_char, int last_char);
int		get_row_length(char *row);
int		should_skip_row(t_map *map, int y, int *len);

// parse_validate_map.c
int		validate_row_borders(t_map *map, int y, int len);
int		check_middle_rows(t_map *map);
int		check_last_row(t_map *map);
int		check_first_row(t_map *map);
int		check_map_borders(t_map *map);

// parse_validate2.c
char	*extract_color(char *line);
char	*skip_to_comma(char *ptr);
char	*parse_rgb_value(char *ptr, int *value, int *has_digits);
int		validate_rgb_component(char **ptr);

// parse_validate1.c
int		check_color_chars(char *color_str, int *commas, int *num_count);
int		check_basic_format(char *color_str, int *commas, int *num_count);
int		validate_color_format(char *color_str);
int		validate_color(char *color, char *name, char *type);
int		validate_all_colors(t_map *map);

// parse_validate.c
int		is_valid_xpm_path(const char *path);
int		validate_texture(char *texture, char *name, char *dir);
int		validate_all_textures(t_map *map);
int		validate_parsing_completeness(t_map *map);

// parse_map2.c
char	*pad_line(char *line, int target_width);
void	fill_map_array(t_map *map, char **lines, int start, int count);
int		calculate_max_width(char **lines, int start, int count);
int		count_map_lines(char **lines, int start_idx, int count);

// parse_map1.c
int		check_empty_line(char **lines, int i, int count);
int		is_valid_map_char(char c);
int		validate_map_char_in_line(char *line);
int		is_map_line(char *line);
int		process_line(char **lines, int i, int *started, int *empty);

// parse_map.c
int		validate_map_continuity(char **lines, int start_idx, int count);
int		parse_map_section(t_map *map, char **lines, int start_idx, int count);
int		process_map_data(t_map *map, char **lines, int i, int line_count);
int		find_map_start(char **lines, int line_count);
int		parse_map(t_map *map, char **lines, int line_count);

// parse_config1.c
char	*copy_string(char *src, int len);
int		parse_ea_texture(t_map *map, char *line);
int		parse_we_texture(t_map *map, char *line);
int		parse_so_texture(t_map *map, char *line);
int		parse_no_texture(t_map *map, char *line);

// parse_config.c
char	*extract_path(char *line);
int		parse_ceiling_color(t_map *map, char *line);
int		parse_floor_color(t_map *map, char *line);
int		parse_config_line(t_map *map, char *line);
int		parse_config(t_map *map);

// reading1.c
int		contain_two_parts(char *str);
char	*extract_line(char *content, int *pos);
char	**allocate_and_fill_lines(char *content, int count, int *lc);
char	**split_lines(char *content, int *line_count);

// reading.c
char	*read_all_file(char *file);
char	**read_and_split_file(char *file, int *line_count);
int		read_file(char *file, t_map *map);

//parsing_utils.c
void	cleanup_lines(char **lines, int line_count);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*skip_spaces(char *str);
int		is_empty(char *line);
int		count_lines_in_content(char *content);

#endif
