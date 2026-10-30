/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

int		bonus_init(t_game *g);
void	bonus_cleanup(t_game *g);
void	bonus_update(t_game *g);
void	bonus_ray_step(t_game *g, int x, int y, int column);
void	bonus_draw(t_game *g);
void	bonus_text(t_game *g);
int		bonus_key(int key, t_game *g);
int		bonus_mouse(int x, int y, t_game *g);
int		bonus_solid(t_game *g, int x, int y);
int		bonus_mini_r(t_game *g);
int		bonus_mini_cx(t_game *g);
int		bonus_mini_cy(t_game *g);
int		bonus_mini_dist2(t_game *g, int x, int y);

#endif
