/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

static void	cleanup_graphics(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->mlx && g->textures[i].handle)
			mlx_destroy_image(g->mlx, g->textures[i].handle);
		i++;
	}
	if (g->mlx && g->frame.handle)
		mlx_destroy_image(g->mlx, g->frame.handle);
	if (g->mlx && g->window)
		mlx_destroy_window(g->mlx, g->window);
	if (g->mlx)
	{
		mlx_do_key_autorepeaton(g->mlx);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

void	cleanup(t_game *g)
{
	int	i;

	feature_cleanup(g);
	cleanup_graphics(g);
	i = 0;
	while (i < 4)
		free(g->paths[i++]);
	i = 0;
	while (i < g->map.height)
		free(g->map.grid[i++]);
	free(g->map.grid);
}

int	close_game(t_game *g)
{
	cleanup(g);
	exit(0);
	return (0);
}
