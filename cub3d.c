/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:26:31 by ayoub             #+#    #+#             */
/*   Updated: 2025/09/14 19:11:57 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int usage(void)
{
	write(2, "Error\nusage: ./cub3D <map.cub>\n", 31);
	return (1);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_game	game;
	t_img	img;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, "game");
	img.img = mlx_new_image(game.mlx, WIN_W, WIN_H);
	// t_app	app;
	// int		rc;

	// if (ac != 2)
	// 	return (usage());
	// rc = app_init(&app, av[1]);
	// if (rc != 0)
	// {
	// 	app_destroy(&app);
	// 	return (1);
	// }
	// rc = app_run(&app);
	// app_destroy(&app);
	// return (rc);
	mlx_loop(game.mlx);
	printf("it works\n");
	return (0);
}
