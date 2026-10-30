/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_sprite_paint_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int	bonus_mix(int a, int b, double t)
{
	int	r;
	int	gr;
	int	bl;

	r = (a >> 16 & 255) + (int)(((b >> 16 & 255) - (a >> 16 & 255)) * t);
	gr = (a >> 8 & 255) + (int)(((b >> 8 & 255) - (a >> 8 & 255)) * t);
	bl = (a & 255) + (int)(((b & 255) - (a & 255)) * t);
	return (r << 16 | gr << 8 | bl);
}

void	bonus_sprite_prepare(t_game *g)
{
	double	t;

	g->bonus.pulse = sin(g->bonus.anim_time * 5);
	t = (g->bonus.pulse + 1) / 2;
	g->bonus.face_color = bonus_mix(0xe46c80, 0xe48db3, t);
	g->bonus.ring_color = bonus_mix(0x622c79, 0x746879, t);
}

static int	bonus_sprite_color(t_game *g, int x, int y, int size)
{
	double	dx;
	double	dy;
	double	d2;

	dx = (2.0 * x - size) / size;
	dy = (2.0 * y - size) / size;
	d2 = dx * dx + dy * dy;
	if (d2 > 0.68 + 0.10 * g->bonus.pulse)
		return (-1);
	if (dy < -0.10 && dy > -0.37
		&& (fabs(dx - 0.28) < 0.09 || fabs(dx + 0.28) < 0.09))
		return (0x172535);
	if (dy > 0.18 && dy < 0.30 && fabs(dx) < 0.35)
		return (0xffd99f);
	if (d2 > 0.48)
		return (g->bonus.ring_color);
	return (g->bonus.face_color);
}

static void	bonus_sprite_column(t_game *g, int x, int left, int size)
{
	int	y;
	int	top;
	int	color;

	top = g->height / 2 - size / 2;
	y = top - 1;
	if (y < -1)
		y = -1;
	while (++y < top + size && y < g->height)
	{
		color = bonus_sprite_color(g, x - left, y - top, size);
		if (color >= 0)
			pixel(&g->frame, x, y, color);
	}
}

void	bonus_sprite_paint(t_game *g, int center, int size, double depth)
{
	int	x;
	int	left;

	if (size < 1)
		return ;
	left = center - size / 2;
	x = left - 1;
	if (x < -1)
		x = -1;
	while (++x < left + size && x < g->width)
	{
		if (depth < g->bonus.rays[x].distance)
			bonus_sprite_column(g, x, left, size);
	}
}
