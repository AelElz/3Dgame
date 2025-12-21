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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	check_file_extension(char *file)
{
	int	i;

	i = ft_strlen(file);
	while (file[i] != '.')
		i--;
	if (ft_strcmp(&file[i], ".cub") && ft_strlen(&file[i]) == 4)
		return (0);
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
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (check_file_extension(av[1]))
	{
		printf("Error: invalid file format\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(game));
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
