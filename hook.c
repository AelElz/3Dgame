/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:23:30 by ael-azha          #+#    #+#             */
/*   Updated: 2025/08/26 17:23:45 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	(void)keycode;
	printf("hello from key_hook\n");
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	printf("Mouse button: %d at (%d, %d)\n", button, x, y);
	return (0);
}
