/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:39:05 by ayoub             #+#    #+#             */
/*   Updated: 2025/09/16 15:04:13 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	win_close(t_game *game)
{
	game->running = false;
	MLX_LOOP_END(game->mlx);
	return (0);
}

int	key_down(int key, t_game *game)
{
	if (key == K_ESC)
		return (win_close(game));
	if (key == K_W)
		game->input.w = 1;
	else if (key == K_A)
		game->input.a = 1;
	else if (key == K_S)
		game->input.s = 1;
	else if (key == K_D)
		game->input.d = 1;
	else if (key == K_LEFT)
		game->input.left = 1;
	else if (key == K_RIGHT)
		game->input.right = 1;
	return (0);
}

int	key_up(int key, t_game *game)
{
	if (key == K_W)
		game->input.w = 0;
	else if (key == K_A)
		game->input.a = 0;
	else if (key == K_S)
		game->input.s = 0;
	else if (key == K_D)
		game->input.d = 0;
	else if (key == K_LEFT)
		game->input.left = 0;
	else if (key == K_RIGHT)
		game->input.right = 0;
	return (0);	
}

int	loop_hook(t_game *game)
{
	double	steps;
	double	rotation;

	if (!game->running)
		return (0);
	steps = game->player.move_spd;
	rotation = game->player.rot_spd;
	if (game->input.w)
		move_fwd(game, steps);
	if (game->input.s)
		move_back(game, steps);
	if (game->input.a)
		move_left(game, steps);
	if (game->input.d)
		move_right(game, steps);
	if (game->input.left)
		turn_left(game, rotation);
	if (game->input.right)
		turn_right(game, rotation);
	draw_frame(game);
	return (0);
}
