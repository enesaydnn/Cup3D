/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

int	feature_can_move(t_game *g, double x, double y)
{
	double	r;

	r = COLLISION_RADIUS;
	return (!bonus_solid(g, (int)floor(x - r), (int)floor(y - r))
		&& !bonus_solid(g, (int)floor(x + r), (int)floor(y - r))
		&& !bonus_solid(g, (int)floor(x - r), (int)floor(y + r))
		&& !bonus_solid(g, (int)floor(x + r), (int)floor(y + r)));
}
