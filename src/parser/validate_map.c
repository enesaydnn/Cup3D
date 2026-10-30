/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parser_walkable(char c);

char	map_at(t_map *map, int x, int y)
{
	if (!map || !map->grid || x < 0 || y < 0
		|| x >= map->width || y >= map->height || !map->grid[y])
		return (' ');
	return (map->grid[y][x]);
}

static int	check_neighbors(t_game *g, int x, int y)
{
	if (map_at(&g->map, x + 1, y) == ' '
		|| map_at(&g->map, x - 1, y) == ' '
		|| map_at(&g->map, x, y + 1) == ' '
		|| map_at(&g->map, x, y - 1) == ' ')
		return (fail(g, "Map opens to void"));
	return (1);
}

static int	check_cell(t_game *g, int x, int y, int *players)
{
	char	c;

	c = map_at(&g->map, x, y);
	if (c != '1' && c != ' ' && !parser_walkable(c))
		return (fail(g, "Invalid map character"));
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if ((*players)++ != 0)
			return (fail(g, "Multiple players"));
		init_player(g, x, y, c);
		g->map.grid[y][x] = '0';
	}
	if (parser_walkable(c) && !check_neighbors(g, x, y))
		return (0);
	return (1);
}

int	validate_map(t_game *g)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			if (!check_cell(g, x, y, &players))
				return (0);
		}
	}
	if (players != 1)
		return (fail(g, "Map must contain one player"));
	return (1);
}
