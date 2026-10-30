/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_draw_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		bonus_minimap(t_game *g);
void	bonus_marker(t_game *g);
void	bonus_rays_draw(t_game *g, int tile);
void	bonus_strip(t_game *g);
void	bonus_panel(t_game *g);
void	bonus_sprites(t_game *g);

void	bonus_draw(t_game *g)
{
	int	tile;

	if (!g->frame.data || !g->bonus.rays)
		return ;
	bonus_sprites(g);
	tile = bonus_minimap(g);
	bonus_rays_draw(g, tile);
	bonus_marker(g);
	bonus_strip(g);
	bonus_panel(g);
}
