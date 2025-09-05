/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:10:59 by ael-azha          #+#    #+#             */
/*   Updated: 2025/08/26 15:14:01 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	iabs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}
int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
int	my_round(float x)
{
	if (x >= 0.0f)
		return ((int)(x + 0.5f));
	return ((int)(x - 0.5f));
}
