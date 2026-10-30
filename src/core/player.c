/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	rotate_player(t_player *p, double angle)
{
	double	c;
	double	s;
	double	x;

	c = cos(angle);
	s = sin(angle);
	x = p->dx;
	p->dx = x * c - p->dy * s;
	p->dy = x * s + p->dy * c;
	x = p->px;
	p->px = x * c - p->py * s;
	p->py = x * s + p->py * c;
}

static void	move_player(t_game *g, double dx, double dy)
{
	if (feature_can_move(g, g->player.x + dx, g->player.y))
		g->player.x += dx;
	if (feature_can_move(g, g->player.x, g->player.y + dy))
		g->player.y += dy;
}

static void	update_player(t_game *g)
{
	double	forward;
	double	strafe;
	double	scale;

	forward = !!(g->keys & FORWARD) - !!(g->keys & BACKWARD);
	strafe = !!(g->keys & RIGHTWARD) - !!(g->keys & LEFTWARD);
	if (forward || strafe)
	{
		scale = MOVE_SPEED * g->dt / sqrt(forward * forward
				+ strafe * strafe);
		move_player(g, (forward * g->player.dx - strafe
				* g->player.dy) * scale, (forward * g->player.dy
				+ strafe * g->player.dx) * scale);
	}
	if ((g->keys & TURN_LEFT) && !(g->keys & TURN_RIGHT))
		rotate_player(&g->player, -TURN_SPEED * g->dt);
	if ((g->keys & TURN_RIGHT) && !(g->keys & TURN_LEFT))
		rotate_player(&g->player, TURN_SPEED * g->dt);
}

int	loop_frame(t_game *g)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	g->dt = now.tv_sec - g->last_time.tv_sec
		+ (now.tv_usec - g->last_time.tv_usec) / 1000000.0;
	g->last_time = now;
	if (g->dt < 0)
		g->dt = 0;
	if (g->dt > 0.05)
		g->dt = 0.05;
	update_player(g);
	feature_update(g);
	render(g);
	return (0);
}
