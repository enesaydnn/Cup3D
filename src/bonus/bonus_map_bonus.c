/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static int	bonus_tile(t_game *g, int x, int y)
{
	char	c;
	int		order;

	if (x < 0 || y < 0 || x >= g->map.width || y >= g->map.height)
		return (0x090e15);
	c = map_at(&g->map, x, y);
	if (g->bonus.debug && g->bonus.show_dda && g->bonus.visible
		&& g->bonus.visited)
	{
		order = g->bonus.visited[y * g->map.width + x];
		if (order && order <= g->bonus.frame % (g->bonus.visible + 1))
			return (0x49775c + (order % 4) * 0x001006);
	}
	if (c == '1')
		return (0x465569);
	if (c == 'D')
		return (0xe09c48);
	if (c == 'd')
		return (0x735a3c);
	if (c == ' ' || c == '\0')
		return (0x090e15);
	if (c == 'P')
		return (0x8c426e);
	return (0x1a2730);
}

static int	bonus_map_color(t_game *g, int x, int y, int tile)
{
	double	mx;
	double	my;
	int		ix;
	int		iy;
	int		color;

	mx = g->player.x + (double)(x - bonus_mini_cx(g)) / tile;
	my = g->player.y + (double)(y - bonus_mini_cy(g)) / tile;
	ix = (int)floor(mx);
	iy = (int)floor(my);
	color = bonus_tile(g, ix, iy);
	if (mx - ix < 1.0 / tile || my - iy < 1.0 / tile)
		return (0x0d151e);
	return (color);
}

static int	bonus_mini_tile(t_game *g)
{
	int	tile;

	tile = 2 * bonus_mini_r(g) / 12;
	if (tile < 1)
		tile = 1;
	if (tile > 20)
		tile = 20;
	return (tile);
}

int	bonus_minimap(t_game *g)
{
	int	x;
	int	y;
	int	r;
	int	d;
	int	tile;

	r = bonus_mini_r(g);
	tile = bonus_mini_tile(g);
	y = bonus_mini_cy(g) - r - 1;
	while (++y <= bonus_mini_cy(g) + r && y < g->height)
	{
		x = bonus_mini_cx(g) - r - 1;
		while (++x <= bonus_mini_cx(g) + r && x < g->width)
		{
			d = bonus_mini_dist2(g, x, y);
			if (d <= (r - 3) * (r - 3))
				pixel(&g->frame, x, y, bonus_map_color(g, x, y, tile));
			else if (d <= r * r)
				pixel(&g->frame, x, y, 0x8a9bb0);
		}
	}
	return (tile);
}
