/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	init_ray(t_game *g, t_ray *r, int x)
{
	mem_zero(r, sizeof(*r));
	r->camera_x = 2.0 * x / g->width - 1.0;
	r->dx = g->player.dx + g->player.px * r->camera_x;
	r->dy = g->player.dy + g->player.py * r->camera_x;
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
	r->delta_x = HUGE_VAL;
	r->delta_y = HUGE_VAL;
	if (r->dx != 0)
		r->delta_x = fabs(1.0 / r->dx);
	if (r->dy != 0)
		r->delta_y = fabs(1.0 / r->dy);
}

static void	init_steps(t_game *g, t_ray *r)
{
	r->step_x = 1;
	r->step_y = 1;
	r->side_x = (r->map_x + 1 - g->player.x) * r->delta_x;
	r->side_y = (r->map_y + 1 - g->player.y) * r->delta_y;
	if (r->dx < 0)
	{
		r->step_x = -1;
		r->side_x = (g->player.x - r->map_x) * r->delta_x;
	}
	if (r->dy < 0)
	{
		r->step_y = -1;
		r->side_y = (g->player.y - r->map_y) * r->delta_y;
	}
}

static void	advance_ray(t_ray *r)
{
	if (r->side_x < r->side_y)
	{
		r->side_x += r->delta_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_y += r->delta_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
	r->steps++;
}

static void	step_ray(t_game *g, t_ray *r, int column)
{
	char	cell;

	while (r->steps < g->map.width + g->map.height)
	{
		advance_ray(r);
		feature_ray_step(g, r->map_x, r->map_y, column);
		cell = map_at(&g->map, r->map_x, r->map_y);
		if (cell == ' ' || cell == '1' || cell == 'D')
		{
			r->hit = (cell != ' ');
			r->door = (cell == 'D');
			return ;
		}
	}
}

void	cast_ray(t_game *g, t_ray *r, int x)
{
	init_ray(g, r, x);
	init_steps(g, r);
	step_ray(g, r, x);
	if (!r->hit)
		return ;
	if (r->side == 0)
	{
		r->distance = r->side_x - r->delta_x;
		r->face = EAST;
		if (r->dx > 0)
			r->face = WEST;
		r->wall_x = g->player.y + r->distance * r->dy;
	}
	else
	{
		r->distance = r->side_y - r->delta_y;
		r->face = SOUTH;
		if (r->dy > 0)
			r->face = NORTH;
		r->wall_x = g->player.x + r->distance * r->dx;
	}
	r->wall_x -= floor(r->wall_x);
}
