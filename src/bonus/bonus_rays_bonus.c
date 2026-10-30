/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_rays_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	bonus_ray_color(t_game *g, int column)
{
	if (!g->bonus.debug)
		return (0xffc000);
	if (column == g->bonus.selected)
		return (0xffffff);
	if (g->width < 2)
		return (0xcc9966);
	return (((255 * (g->width - 1 - column) / (g->width - 1)) << 16)
		| (150 << 8) | (255 * column / (g->width - 1)));
}

static void	bonus_trace(t_game *g, int column, int tile)
{
	double	d;
	double	limit;
	int		x;
	int		y;
	t_ray	*ray;

	ray = &g->bonus.rays[column];
	limit = ray->distance;
	if (limit > (double)bonus_mini_r(g) / tile)
		limit = (double)bonus_mini_r(g) / tile;
	d = 0;
	while (ray->hit && d <= limit)
	{
		x = bonus_mini_cx(g) + (int)(ray->dx * d * tile);
		y = bonus_mini_cy(g) + (int)(ray->dy * d * tile);
		if (x < g->width && y < g->height && bonus_mini_dist2(g, x, y)
			< (bonus_mini_r(g) - 3) * (bonus_mini_r(g) - 3))
			pixel(&g->frame, x, y, bonus_ray_color(g, column));
		d += 0.5 / tile;
	}
}

void	bonus_rays_draw(t_game *g, int tile)
{
	int	x;
	int	step;

	if (!g->bonus.rays)
		return ;
	step = g->bonus.step;
	if (!g->bonus.debug)
		step = g->width / 24;
	if (step < 1)
		step = 1;
	x = 0;
	while (x < g->width)
	{
		bonus_trace(g, x, tile);
		x += step;
	}
	if (g->bonus.debug)
		bonus_trace(g, g->bonus.selected, tile);
	else
		bonus_trace(g, g->width - 1, tile);
}

void	bonus_strip(t_game *g)
{
	int	x;
	int	y;

	if (!g->bonus.debug)
		return ;
	y = -1;
	while (++y < g->height / 25)
	{
		x = -1;
		while (++x < g->width)
			pixel(&g->frame, x, y, bonus_ray_color(g, x));
	}
}
