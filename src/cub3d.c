/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:40:21 by ael-azha          #+#    #+#             */
/*   Updated: 2025/11/04 14:48:38 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../includes/libft.h"

int	ft_error(void)
{
	printf("Error: ./cub3D <map.cub>\n");
	return (1);
}

int	reading_map(char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Can't open the file\n");
		return (1);
	}
	printf("%d\n%s", fd, get_next_line(fd));
	return (0);
}

int main(int ac, char **av)
{
	t_game	game;
	int		rc;

	if (ac != 2)
		return (ft_error());
	
	if (reading_map(av[1]))
		return (1);
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
