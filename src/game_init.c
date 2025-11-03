/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:56:16 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/03 22:48:23 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void build_fallback_map(t_game *g)
{
    static const char *rows[] = {
        "1111111111",
        "1000000001",
        "1011111101",
        "1000000101",
        "100E000101",
        "1010110101",
        "1010000101",
        "1011111101",
        "1000000001",
        "1111111111",
    };
    const int H = (int)(sizeof(rows) / sizeof(rows[0]));
    int i, j;

    if (g->map.grid) return; /* already set by parser */

    g->map.height = H;
    g->map.width  = (int)strlen(rows[0]);
    g->map.grid   = (char **)malloc(sizeof(char*) * g->map.height);
    if (!g->map.grid)
		return;

    for (i = 0; i < g->map.height; ++i)
	{
        g->map.grid[i] = strdup(rows[i]);
        if (!g->map.grid[i]) return;
    }

    for (i = 0; i < g->map.height; ++i)
	{
        for (j = 0; j < g->map.width; ++j)
		{
            char c = g->map.grid[i][j];
            if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
                g->map.spawn.x   = j;
                g->map.spawn.y   = i;
                g->map.spawn_dir = c;
                g->map.grid[i][j]= '0';
                return;
            }
        }
    }
}

static void set_defaults_if_empty(t_game *game)
{
    if (game->map.top_col.r == 0 && game->map.top_col.g == 0 && game->map.top_col.b == 0 &&
        game->map.floor_col.r == 0 && game->map.floor_col.g == 0 && game->map.floor_col.b == 0)
    {
        game->map.top_col   = (t_rgba){153, 204, 255, 0}; /* sky */
        game->map.floor_col = (t_rgba){ 51,  51,  51, 0}; /* dark floor */
    }
}

static void set_player_spawn(t_game *game)
{
    if (game->map.spawn_dir == 0)
	{
        game->map.spawn.x = 2;
        game->map.spawn.y = 2;
        game->map.spawn_dir = 'E';
    }
    game->player.pos.x = (double)game->map.spawn.x + 0.5;
    game->player.pos.y = (double)game->map.spawn.y + 0.5;

    if      (game->map.spawn_dir == 'N') { game->player.dir.x =  0.0; game->player.dir.y = -1.0; }
    else if (game->map.spawn_dir == 'E') { game->player.dir.x =  1.0; game->player.dir.y =  0.0; }
    else if (game->map.spawn_dir == 'S') { game->player.dir.x =  0.0; game->player.dir.y =  1.0; }
    else                                 { game->player.dir.x = -1.0; game->player.dir.y =  0.0; }

    game->player.move_spd = 0.08;
    game->player.rot_spd  = 0.05;
    cam_make_plane(&game->player, FOV_DEG);
}

int game_init(t_game *game, const char *cub_path)
{
    int rc;
    (void)cub_path;

    ft_memset(game, 0, sizeof(*game));
    set_defaults_if_empty(game);
    build_fallback_map(game);
    game->mlx = mlx_init();
    if (!game->mlx)
        return (printf("mlx_init failed\n"), 1);
    game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "lo3ba_3d");
    if (!game->win)
        return (printf("mlx_new_window failed\n"), 1);
		
    mlx_hook(game->win, 2, 1L<<0, key_down, game);
    mlx_hook(game->win, 3, 1L<<1, key_up, game);
    mlx_hook(game->win, 17, 0,     win_close, game);
    mlx_loop_hook(game->mlx, loop_hook, game);
	
    rc = img_new(game, &game->frame, WIN_W, WIN_H);
    if (rc != 0 || !game->frame.img || !game->frame.pixels)
        return (printf("frame create failed\n"), 1);
    set_player_spawn(game);
    game->running = true;
    return (0);
}

int game_run(t_game *game)
{
    if (!game->mlx || !game->win)
        return (printf("invalid game\n"));
    mlx_loop(game->mlx);
    return (0);
}

void game_free(t_game *game)
{
    img_free(game, &game->tex.no);
    img_free(game, &game->tex.so);
    img_free(game, &game->tex.we);
    img_free(game, &game->tex.ea);
    img_free(game, &game->frame);
	
    if (game->map.grid)
	{
        for (int i = 0; i < game->map.height; ++i)
            free(game->map.grid[i]);
        free(game->map.grid);
        game->map.grid = NULL;
    }
    if (game->win)
	{
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
    }
#ifdef __linux__
    if (game->mlx) {
        mlx_destroy_display(game->mlx);
    }
#endif
    game->mlx = NULL;
}
