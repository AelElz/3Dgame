/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:56:16 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/23 21:52:52 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	copy_rows_to_map(t_game *g, char **rows, int h)
{
	int	i;

	g->map.height = h;
	g->map.width = (int)ft_strlen(rows[0]);
	g->map.grid = (char **)malloc(sizeof(char *) * g->map.height);
	if (!g->map.grid)
		return ;
	i = 0;
	while (i < g->map.height)
	{
		g->map.grid[i] = ft_strdup(rows[i]);
		if (!g->map.grid[i])
			return ;
		i++;
	}
}

void	find_spawn(t_game *g)
{
	int	i;
	int	j;
	char	c;

	i = -1;
	while (++i < g->map.height)
	{
		j = -1;
		while (++j < g->map.width)
		{
			c = g->map.grid[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				g->map.spawn.x = j;
				g->map.spawn.y = i;
				g->map.spawn_dir = c;
				g->map.grid[i][j] = '0';
				return ;
			}
		}
	}
}

void	build_fallback_map(t_game *g)
{
	char	*rows[] =
	{
		"11111111111111111",
		"10000000000000001",
		"10000000N00000001",
		"11111111111111111"
	};
	int	h;

	if (g->map.grid)
		return ;
	h = (int)(sizeof(rows) / sizeof(rows[0]));
	copy_rows_to_map(g, rows, h);
	find_spawn(g);
}
