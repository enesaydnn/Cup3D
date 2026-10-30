/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	player_overlaps(t_game *g, int x, int y)
{
	double	r;

	r = COLLISION_RADIUS;
	return (g->player.x + r > x && g->player.x - r < x + 1
		&& g->player.y + r > y && g->player.y - r < y + 1);
}

static double	door_distance(t_game *g, int x, int y)
{
	double	dx;
	double	dy;

	if (x < 0 || y < 0 || x >= g->map.width || y >= g->map.height
		|| player_overlaps(g, x, y))
		return (4);
	if (map_at(&g->map, x, y) != 'D'
		&& map_at(&g->map, x, y) != 'd')
		return (4);
	dx = x + 0.5 - g->player.x;
	dy = y + 0.5 - g->player.y;
	if (dx * g->player.dx + dy * g->player.dy <= 0)
		return (4);
	return (dx * dx + dy * dy);
}

static void	bonus_door(t_game *g)
{
	int		x;
	int		y;
	int		best_x;
	int		best_y;
	double	best;

	best = 4;
	best_x = -1;
	y = (int)g->player.y - 2;
	while (++y <= (int)g->player.y + 1)
	{
		x = (int)g->player.x - 2;
		while (++x <= (int)g->player.x + 1)
		{
			if (door_distance(g, x, y) < best)
			{
				best = door_distance(g, x, y);
				best_x = x;
				best_y = y;
			}
		}
	}
	if (best_x >= 0)
		g->map.grid[best_y][best_x] ^= 'D' ^ 'd';
}

int	bonus_key(int key, t_game *g)
{
	if (key == 'e' || key == 'E')
		bonus_door(g);
	else if (key == 0xff09)
		g->bonus.debug = !g->bonus.debug;
	else if (key == '[' && g->bonus.step > 1)
		g->bonus.step--;
	else if (key == ']' && g->bonus.step < g->width)
		g->bonus.step++;
	else if ((key == 'j' || key == 'J') && g->bonus.selected > 0)
		g->bonus.selected--;
	else if ((key == 'k' || key == 'K')
		&& g->bonus.selected < g->width - 1)
		g->bonus.selected++;
	else if (key == 'v' || key == 'V')
		g->bonus.show_dda = !g->bonus.show_dda;
	return (0);
}

int	bonus_mouse(int x, int y, t_game *g)
{
	(void)y;
	if (g->bonus.mouse_ready && g->width > 0)
		rotate_player(&g->player,
			(double)(x - g->bonus.mouse_x) * TURN_SPEED / g->width);
	g->bonus.mouse_x = x;
	g->bonus.mouse_ready = 1;
	return (0);
}
