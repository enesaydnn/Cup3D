/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_sprites_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <float.h>

void	bonus_sprite_paint(t_game *g, int center, int size, double depth);
void	bonus_sprite_prepare(t_game *g);

static double	bonus_sprite_depth(t_game *g, int x, int y)
{
	if (map_at(&g->map, x, y) != 'P')
		return (0);
	return ((x + 0.5 - g->player.x) * g->player.dx
		+ (y + 0.5 - g->player.y) * g->player.dy);
}

static int	bonus_next_sprite(t_game *g, double *limit, int *last)
{
	int		x;
	int		y;
	int		choice;
	double	depth;
	double	best;

	choice = -1;
	best = 0;
	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			depth = bonus_sprite_depth(g, x, y);
			if (depth > 0.1 && depth > best && (depth < *limit
					|| (depth == *limit && y * g->map.width + x > *last)))
			{
				choice = y * g->map.width + x;
				best = depth;
			}
		}
	}
	*limit = best;
	return (*last = choice, choice);
}

static void	bonus_project_sprite(t_game *g, int index)
{
	double	det;
	double	rx;
	double	ry;
	double	depth;
	double	lateral;

	rx = index % g->map.width + 0.5 - g->player.x;
	ry = index / g->map.width + 0.5 - g->player.y;
	det = g->player.px * g->player.dy
		- g->player.dx * g->player.py;
	if (det == 0)
		return ;
	lateral = (g->player.dy * rx - g->player.dx * ry) / det;
	depth = (-g->player.py * rx + g->player.px * ry) / det;
	if (depth > 0.1)
		bonus_sprite_paint(g, (int)((1 + lateral / depth) * g->width / 2),
			(int)(g->height / depth), depth);
}

void	bonus_sprites(t_game *g)
{
	double	limit;
	int		last;
	int		index;

	if (!g->bonus.rays)
		return ;
	bonus_sprite_prepare(g);
	limit = DBL_MAX;
	last = -1;
	index = bonus_next_sprite(g, &limit, &last);
	while (index >= 0)
	{
		bonus_project_sprite(g, index);
		index = bonus_next_sprite(g, &limit, &last);
	}
}
