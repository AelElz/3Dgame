/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:56:16 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/01 17:16:29 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_spawn(t_game *game)//had function in case 3gezty dir spawn fil parsin
{
	if (game->map.spawn.x == 0 && game->map.spawn.y == 0 &&
		game->map.spawn_dir == 0)
	{
		game->map.spawn.x = 2;
		game->map.spawn.y = 2;
		game->map.spawn_dir = 'E';		
	}
	game->player.pos.x = (double)game->map.spawn.x + 0.5;
    game->player.pos.y = (double)game->map.spawn.y + 0.5;
	if (game->map.spawn_dir == 'N')
	{
		game->player.dir.x = 0.0;
		game->player.dir.y = -1.0;
	}
	else if (game->map.spawn_dir == 'E')
	{
		game->player.dir.x = 1.0;
		game->player.dir.y = 0.0;
	}
	else if (game->map.spawn_dir == 'S')
	{
		game->player.dir.x = 0.0;
		game->player.dir.y = 1.0;
	}
	else if (game->map.spawn_dir == 'W')
	{
		game->player.dir.x = -1.0;
		game->player.dir.y = 0.0;
	}
	game->player.move_spd = 0.08;
	game->player.rot_spd = 0.05;
	cam_make_plane(&game->player, FOV_DEG);
}

int	game_init(t_game *game, const char *cub_path)
{
	int	rc;
	(void)cub_path;

	ft_memset(game, 0, sizeof(*game));
	rc = 0;
	if (game->map.top_col.r == 0 && game->map.floor_col.r == 0
			&& game->map.top_col.g == 0 && game->map.floor_col.g == 0
			&& game->map.top_col.b == 0 && game->map.floor_col.b == 0)
	{
		game->map.top_col = (t_rgba){153, 204, 255, 0};//bleu ceil sky
		game->map.floor_col = (t_rgba){51, 51, 51, 0};//dark gray floor
	}
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	mlx_hook(game->win, 2, 1L<<0, key_down, game);
	mlx_hook(game->win, 3, 1L<<1, key_up, game);
	mlx_hook(game->win, 17, 0, win_close, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	rc = img_new(game, &game->frame, WIN_W, WIN_H);
	if (rc != 0)
		return (printf("frame create failed\n"));
	set_player_spawn(game);
	game->running = true;
	return (0);
}

int	game_run(t_game *game)
{
	if (!game->mlx || !game->win)
		return (printf("invalid game\n"));
	mlx_loop(game->mlx);
	return (0);
}

void	game_free(t_game *game)
{
	img_free(game, &game->tex.no);
	img_free(game, &game->tex.so);
	img_free(game, &game->tex.we);
	img_free(game, &game->tex.ea);
	img_free(game, &game->frame);
 	 if (game->win)
 	 	mlx_destroy_window(game->mlx, game->win);
  #ifdef __linux__
	if (game->mlx)
		mlx_destroy_display(game->mlx, game->win);//hado for la khdemt b linux
#endif

	//mol parsin free map fi had lblasa !!!!
}
