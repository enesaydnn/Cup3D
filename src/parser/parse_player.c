/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *g, int x, int y, char direction)
{
	g->player.x = x + 0.5;
	g->player.y = y + 0.5;
	g->player.dx = 0;
	g->player.dy = 0;
	if (direction == 'N')
		g->player.dy = -1;
	else if (direction == 'S')
		g->player.dy = 1;
	else if (direction == 'W')
		g->player.dx = -1;
	else if (direction == 'E')
		g->player.dx = 1;
	g->player.px = -g->player.dy * PLANE_SCALE;
	g->player.py = g->player.dx * PLANE_SCALE;
}
