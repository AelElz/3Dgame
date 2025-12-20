#include "parsing.h"

int	parse_first_six(t_game *game)
{
	int	i;
	int	count_lines;

	i = 0;
	count_lines = 0;
	while (game->p->file[i] && count_lines < 6)
	{
		if (!is_empty(game->p->file[i]))
		{
			if (contain_two_parts(game->p->file[i]))
			{
				game->p->first_six[count_lines] = ft_strdup(game->p->file[i]);
				remove_newline(game->p->first_six[count_lines]);
				count_lines++;
			}
			else
				exiting("Error: invalid element line\n", game);
		}
		i++;
	}
	if (count_lines < 6)
		exiting("Error: missing elements\n", game);
	game->p->first_six[count_lines] = NULL;
	return (i);
}

int map_ended(char **map, int j)
{
	if (!map[j])
		return (1);
	while (map[j])
	{
		if (!is_empty(map[j]))
			return (0);
		j++;
	}
	return (1);
}

int	calculate_width(char **map, int height)
{
	int	max_w;
	int	len;
	int	i;

	max_w = 0;
	i = 0;
	while (i < height)
	{
		if (map[i])
		{
			len = ft_strlen(map[i]);
			if (len > max_w)
				max_w = len;
		}
		i++;
	}
	return (max_w);
}

void	parse_map(t_game *game, int i)
{
	int j;

	j = i;
	while (game->p->file[j])
		j++;
	game->map.map = malloc(sizeof(char *) * (j + 1));
	if (!game->map.map)
		exiting("Error: malloc\n", game);
	memset(game->map.map, 0, sizeof(char *) * (j + 1));
	j = 0;
	while (game->p->file[i] && !map_ended(game->p->file, i))
	{
		game->map.map[j] = ft_strdup(game->p->file[i]);
		remove_newline(game->map.map[j]);
		j++;
		i++;
	}
	game->map.map[j] = NULL;
	game->p->has_map = 1;
	game->map.height = j;
	game->map.width = calculate_width(game->map.map, j);
	// printf ("%d\n%d\n", game->map.height, game->map.width);
	// i = 0;
	// while (game->map.map[i])
	// 	printf("%s\n", game->map.map[i++]);
}

void	parse_file(t_game *game)
{
	int i;

	game->p->first_six = malloc(sizeof(char *) * 7);
	if (!game->p->first_six)
		exiting("Error: malloc\n", game);
	memset(game->p->first_six, 0, sizeof(char *) * 7);
	i = parse_first_six(game);
	while (game->p->file[i] && is_empty(game->p->file[i]))
		i++;
	if (game->p->file[i])
		parse_map(game, i);
	else
	{
		game->map.map = NULL;
		game->p->has_map = 0;
	}
}

void init_elements_splited(t_elements_splited *elements_splited)
{
	elements_splited->f = NULL;
	elements_splited->c = NULL;
	elements_splited->no = NULL;
	elements_splited->so = NULL;
	elements_splited->we = NULL;
	elements_splited->ea = NULL;
}

int	is_map(char c)
{
	if (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	validate_map(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (game->map.map && game->map.map[j])
	{
		while (game->map.map[j][i] == ' ' || game->map.map[j][i] == '\t')
			i++;
		while (game->map.map[j][i] && game->map.map[j][i] != '\n')
		{
			if (!is_map(game->map.map[j][i]))
				exiting("Error: invalid map\n", game);
			i++;
		}
		if (game->map.map[j][i] == '\n' && map_ended(game->map.map, j + 1))
			break ;
		if (game->map.map[j][i] == '\n' && (!game->map.map[j + 1] || is_empty(game->map.map[j + 1])))
			exiting("Error: invalid map-----\n", game);
		j++;
		i = 0;
		// printf("%s is valid\n", game->map.map[j]);
	}
}



int is_valid_neighbor(t_game *game, int col, int row)
{
    if (col < 0 || col >= game->map.height || row < 0)
        return (0);
    if (row >= (int)ft_strlen(game->map.map[col]))
        return (0);
    return (1);
}

void	check_walkable_spaces(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < (int)ft_strlen(game->map.map[i]))
        {
            if (game->map.map[i][j] == '0' || game->map.map[i][j] == 'N' ||
                game->map.map[i][j] == 'S' || game->map.map[i][j] == 'E' ||
                game->map.map[i][j] == 'W')
            {
                if (!is_valid_neighbor(game, i - 1, j) ||
                    !is_valid_neighbor(game, i + 1, j) ||
                    !is_valid_neighbor(game, i, j - 1) ||
                    !is_valid_neighbor(game, i, j + 1))
					exiting("Error: map not valid (walkable space not enclosed)\n", game);
            }
            j++;
        }
        i++;
    }
}

int check_side_walls(t_game *game)
{
	int i;
	int len;

	i = 0;
	while (i < game->map.height)
	{
		len = ft_strlen(game->map.map[i]);
		if (len > 0)
		{
			if (game->map.map[i][0] != '1' && game->map.map[i][0] != ' ' && game->map.map[i][0] != '\t')
				return (0);
			if (game->map.map[i][len - 1] != '1' && game->map.map[i][len - 1] != ' ' && game->map.map[i][len - 1] != '\t')
				return (0);
		}
		i++;
	}
	return (1);
}

int check_top_bottom_walls(t_game *game, int col)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(game->map.map[col]);
	while (i < len)
	{
		if (game->map.map[col][i] != '1' && game->map.map[col][i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	check_map_borders(t_game *game)
{
    if (!game->p || !game->map.map || game->map.height == 0)
		return ;
    if (!check_top_bottom_walls(game, 0))
		exiting("Error: map is not closed (top wall)\n", game);
    if (!check_top_bottom_walls(game, game->map.height - 1))
		exiting("Error: map is not closed (bottom wall)\n", game);
	if (!check_side_walls(game))
		exiting("Error: map is not closed (side wall)\n", game);
	check_walkable_spaces(game);
}

void	set_player_angle(t_game *game, char c)
{
	if (c == 'N')
		game->map.player.angle = 270.0;
	else if (c == 'S')
		game->map.player.angle = 90.0;
	else if (c == 'W')
		game->map.player.angle = 180.0;
	else if (c == 'E')
		game->map.player.angle = 0.0;
}

void	player_found(t_game *game, int x, int y, int *player_count)
{
	char	c;

	if (*player_count > 0)
		exiting("Error: Multiple players in the map\n", game);
	c = game->map.map[y][x];
	game->map.player.player_x = (double)x + 0.5;
	game->map.player.player_y = (double)y + 0.5;
	set_player_angle(game, c);
	(void)c;
	game->map.map[y][x] = '0';
	(*player_count)++;
}

void	find_player(t_game *game, int *player_count)
{
	int		x;
	int		y;
	char	c;

	*player_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.map[y][x])
		{
			c = game->map.map[y][x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				player_found(game, x, y, player_count);
			x++;
		}
		y++;
	}
}

void	validate_player(t_game *game)
{
	int	player_count;

	player_count = 0;
	find_player(game, &player_count);
	if (player_count == 0)
		exiting("Error: No player in the map\n", game);
	else if (player_count > 1)
		exiting("Error: Multiple players in the map", game);
}

void	main_parsing(t_game *game)
{

	game->p->first_six = NULL;
	init_elements_splited(&game->p->elements_splited);
	// memset(&p->map.player, 0, sizeof(t_player_info));
	parse_file(game);
	if (!game->p->has_map)
		exiting("Error: missing map\n", game);
	parse_first_elements(game);
	validate_map(game);
	check_map_borders(game);
	parse_key_value(game);
	validate_player(game);
	// game->map.grid = game->map.map;
	// printf("map height = %d\n", game->map.height);
	// printf("floor color = %s\n", game->map.floor_color);

}
