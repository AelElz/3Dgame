/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:44:37 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/11 17:59:47 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_spawn_dir_values(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir.x = 0.0;
		p->dir.y = -1.0;
	}
	else if (dir == 'E')
	{
		p->dir.x = 1.0;
		p->dir.y = 0.0;
	}
	else if (dir == 'S')
	{
		p->dir.x = 0.0;
		p->dir.y = 1.0;
	}
	else
	{
		p->dir.x = -1.0;
		p->dir.y = 0.0;
	}
}

void	set_player_spawn(t_game *game)
{
	if (game->map.spawn_dir == 0)
	{
		game->map.spawn = (t_ind2){2, 2};
		game->map.spawn_dir = 'E';
	}
	game->player.pos.x = (double)game->map.spawn.x + 0.5;
	game->player.pos.y = (double)game->map.spawn.y + 0.5;
	set_spawn_dir_values(&game->player, game->map.spawn_dir);
	game->player.move_spd = 0.05;
	game->player.rot_spd = 0.03;
	cam_make_plane(&game->player, FOV_DEG);
}
