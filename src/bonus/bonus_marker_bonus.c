/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_marker_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	bonus_marker_dot(t_game *g, int px, int py)
{
	int	x;
	int	y;

	y = -3;
	while (++y <= 3)
	{
		x = -3;
		while (++x <= 3)
			if (x * x + y * y <= 9 && px + x >= 0 && py + y >= 0
				&& px + x < g->width && py + y < g->height)
				pixel(&g->frame, px + x, py + y, 0xffe5aa);
	}
}

void	bonus_marker(t_game *g)
{
	int	x;
	int	y;
	int	i;
	int	px;
	int	py;

	px = bonus_mini_cx(g);
	py = bonus_mini_cy(g);
	i = 0;
	while (i < 12)
	{
		x = px + (int)(g->player.dx * i);
		y = py + (int)(g->player.dy * i);
		if (x >= 0 && y >= 0 && x < g->width && y < g->height)
			pixel(&g->frame, x, y, 0xf8db85);
		i++;
	}
	bonus_marker_dot(g, px, py);
}
