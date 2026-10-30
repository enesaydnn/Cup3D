/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"

int	feature_init(t_game *g)
{
	return (bonus_init(g));
}

void	feature_cleanup(t_game *g)
{
	bonus_cleanup(g);
}

void	feature_hooks(t_game *g)
{
	mlx_hook(g->window, 6, 1L << 6, bonus_mouse, g);
}

void	feature_focus(t_game *g)
{
	g->bonus.mouse_ready = 0;
}

void	feature_key(int key, t_game *g)
{
	bonus_key(key, g);
}
