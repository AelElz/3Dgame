/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:43:49 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 21:44:00 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_defaults_if_empty(t_game *game)
{
	int	*tc;
	int	*fc;

	tc = (int *)&game->map.top_col;
	fc = (int *)&game->map.floor_col;
	if (*tc == 0 && *fc == 0)
	{
		game->map.top_col = (t_rgba){153, 204, 255, 0};
		game->map.floor_col = (t_rgba){51, 51, 51, 0};
	}
}