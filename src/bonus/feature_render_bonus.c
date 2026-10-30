/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	feature_update(t_game *g)
{
	bonus_update(g);
}

void	feature_store_ray(t_game *g, t_ray *ray, int x)
{
	g->bonus.rays[x] = *ray;
}

void	feature_ray_step(t_game *g, int x, int y, int column)
{
	bonus_ray_step(g, x, y, column);
}

void	feature_draw(t_game *g)
{
	bonus_draw(g);
}

void	feature_text(t_game *g)
{
	bonus_text(g);
}
