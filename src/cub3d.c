/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:40:21 by ael-azha          #+#    #+#             */
/*   Updated: 2025/12/21 20:01:32 by ael-azha         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_game	game;
	int		rc;

	if (ac != 2)
		return (ft_error());
	if (!is_valid_cub_filename(av[1]))
	{
		printf("Error: Invalid map filename. Must be <name>.cub\n");
		return (1);
	}
	rc = game_init(&game, av[1]);
	if (rc != 0)
	{
		game_free(&game);
		return (1);
	}
	rc = game_run(&game);
	game_free(&game);
	return (rc);
}
