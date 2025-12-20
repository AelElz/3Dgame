/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:40:21 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/17 21:03:12 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_error(void)
{
	printf("Error: ./cub3D <map.cub>\n");
	return (1);
}

int	is_valid_cub_filename(char *filename)
{
	int		len;
	char	*last_slash;
	char	*basename;

	if (!filename)
		return (0);
	last_slash = ft_strrchr(filename, '/');
	if (last_slash)
		basename = last_slash + 1;
	else
		basename = filename;
	if (!basename || !*basename)
		return (0);
	if (basename[0] == '.')
		return (0);
	len = ft_strlen(basename);
	if (len < 5)
		return (0);
	if (ft_strncmp(basename + len - 4, ".cub", 4) != 0)
		return (0);
	if (len == 4)
		return (0);
	return (1);
}

void	print_everything(t_game *game)
{
	int	i = 0;
	printf("map height = %d\n", game->map.height);
	printf("map width =  %d\n", game->map.width);
	printf("------------map------------\n");
	i = 0;
	while (i < game->map.height)
	printf("%s\n", game->map.map[i++]);
	printf("---------------------------\n");
	printf("NO Texture = %s\n", game->map.no_texture);
	printf("SO Texture = %s\n", game->map.so_texture);
	printf("WE Texture = %s\n", game->map.we_texture);
	printf("EA Texture = %s\n", game->map.ea_texture);
	printf("F Color =    %s\n", game->map.floor_color);
	printf("C Color =    %s\n", game->map.ceiling_color);
	printf("Spawn dir =  %c\n", game->map.spawn_dir);
	printf("---------------------------\n");
}

int	main(int ac, char **av)
{
	t_game	game;
	int		rc;

	// if (ac != 2)
	// 	return (ft_error());
	// if (!is_valid_cub_filename(av[1]))
	// {
	// 	printf("Error: Invalid map filename. Must be <name>.cub\n");
	// 	return (1);
	// }
	
	ft_memset(&game, 0, sizeof(t_game));
	game.p = malloc (sizeof(t_parsing));
	memset(game.p, 0, sizeof(t_parsing));
	if (ac != 2)
		exiting("Error: invalid arguments\n", &game);
	if (check_the_file_extension(av[1]))
		exiting("Error: invalid file format\n", &game);
	game.p->file = read_file(av[1]);
	if (!game.p->file)
		exiting("Error: failed to read file\n", &game);
	
	// main_parsing(p);
	// int i = 0;
	// while (p->file[i])
	// 	printf("%s\n", p->file[i++]);

	// ft_memset(&game, 0, sizeof(game));
	// game.map = p->map;
	main_parsing(&game);
	rc = game_init(&game, av[1]);
	print_everything(&game);
	if (rc != 0)
	{
		game_free(&game);
		return (1);
	}
	
	// printf("%s\n", game.map.ceiling_color);
	// printf("%s\n", p->map.ceiling_color);
	rc = game_run(&game);
	game_free(&game);
	exiting(NULL, &game);
	return (rc);
}
