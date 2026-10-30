/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_circle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/10/22 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bonus_mini_r(t_game *g)
{
	int	r;

	r = g->height / 7;
	if (r < 24)
		r = 24;
	return (r);
}

int	bonus_mini_cx(t_game *g)
{
	return (8 + bonus_mini_r(g));
}

int	bonus_mini_cy(t_game *g)
{
	return (8 + g->bonus.debug * (g->height / 25) + bonus_mini_r(g));
}

int	bonus_mini_dist2(t_game *g, int x, int y)
{
	int	dx;
	int	dy;

	dx = x - bonus_mini_cx(g);
	dy = y - bonus_mini_cy(g);
	return (dx * dx + dy * dy);
}
