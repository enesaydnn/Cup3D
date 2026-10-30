/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_state_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

int	bonus_init(t_game *g)
{
	if (g->width <= 0 || g->map.width <= 0 || g->map.height <= 0
		|| g->map.width > INT_MAX / g->map.height
		|| (size_t)g->width > SIZE_MAX / sizeof(t_ray)
		|| (size_t)g->map.width > SIZE_MAX / (size_t)g->map.height
		/ sizeof(int))
		return (0);
	mem_zero(&g->bonus, sizeof(t_bonus));
	g->bonus.rays = malloc((size_t)g->width * sizeof(t_ray));
	g->bonus.visited = malloc((size_t)g->map.width * g->map.height
			* sizeof(int));
	if (!g->bonus.rays || !g->bonus.visited)
		return (bonus_cleanup(g), 0);
	mem_zero(g->bonus.rays, (size_t)g->width * sizeof(t_ray));
	mem_zero(g->bonus.visited, (size_t)g->map.width * g->map.height
		* sizeof(int));
	g->bonus.selected = g->width / 2;
	g->bonus.step = 8;
	g->bonus.show_dda = 1;
	return (1);
}

void	bonus_cleanup(t_game *g)
{
	free(g->bonus.rays);
	free(g->bonus.visited);
	g->bonus.rays = NULL;
	g->bonus.visited = NULL;
}

void	bonus_update(t_game *g)
{
	g->bonus.visible = 0;
	if (g->dt > 0 && g->dt < 1)
		g->bonus.anim_time += g->dt;
	if (g->bonus.anim_time > 1000)
		g->bonus.anim_time -= 1000;
	g->bonus.frame = (int)(g->bonus.anim_time * 5);
}

void	bonus_ray_step(t_game *g, int x, int y, int column)
{
	int	i;

	if (!g->bonus.visited || column != g->bonus.selected)
		return ;
	if (g->bonus.visible == 0)
	{
		i = 0;
		while (i < g->map.width * g->map.height)
			g->bonus.visited[i++] = 0;
	}
	if (x < 0 || y < 0 || x >= g->map.width || y >= g->map.height)
		return ;
	i = y * g->map.width + x;
	if (g->bonus.visited[i] == 0)
		g->bonus.visited[i] = ++g->bonus.visible;
}

int	bonus_solid(t_game *g, int x, int y)
{
	char	c;

	if (x < 0 || y < 0 || x >= g->map.width || y >= g->map.height)
		return (1);
	c = map_at(&g->map, x, y);
	return (c == '1' || c == 'D' || c == ' ' || c == '\0');
}
