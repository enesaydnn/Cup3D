/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <stdlib.h>

static int	grow_grid(t_game *g, int *capacity)
{
	char	**grid;
	int		next;
	int		i;

	next = 16;
	if (*capacity)
	{
		next = INT_MAX - 1;
		if (*capacity < (INT_MAX - 1) / 2)
			next = *capacity * 2;
	}
	if ((size_t)next + 1 > (size_t)-1 / sizeof(*grid))
		return (fail(g, "Map is too large"));
	grid = malloc(((size_t)next + 1) * sizeof(*grid));
	if (!grid)
		return (fail(g, "Out of memory"));
	i = -1;
	while (++i < g->map.height)
		grid[i] = g->map.grid[i];
	grid[i] = NULL;
	free(g->map.grid);
	g->map.grid = grid;
	*capacity = next;
	return (1);
}

int	parser_map_line(t_game *g, const char *line, int *capacity)
{
	size_t	len;

	len = str_len(line);
	if (len > INT_MAX - 1 || g->map.height >= INT_MAX - 1)
		return (fail(g, "Map is too large"));
	if (g->map.height == *capacity && !grow_grid(g, capacity))
		return (0);
	g->map.grid[g->map.height] = str_copy_range(line, len);
	if (!g->map.grid[g->map.height])
		return (fail(g, "Out of memory"));
	g->map.height++;
	g->map.grid[g->map.height] = NULL;
	if ((int)len > g->map.width)
		g->map.width = (int)len;
	return (1);
}

static int	pad_row(t_game *g, int y)
{
	char	*row;
	int		x;

	if (str_len(g->map.grid[y]) == (size_t)g->map.width)
		return (1);
	row = malloc((size_t)g->map.width + 1);
	if (!row)
		return (fail(g, "Out of memory"));
	x = -1;
	while (++x < g->map.width)
		row[x] = ' ';
	x = -1;
	while (g->map.grid[y][++x])
		row[x] = g->map.grid[y][x];
	row[g->map.width] = '\0';
	free(g->map.grid[y]);
	g->map.grid[y] = row;
	return (1);
}

int	parser_finish_map(t_game *g)
{
	int	y;

	y = 0;
	while (y < g->map.height)
	{
		if (!pad_row(g, y))
			return (0);
		y++;
	}
	return (validate_map(g));
}
