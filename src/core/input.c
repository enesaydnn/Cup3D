/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	key_mask(int key)
{
	if (key == 'w' || key == 'W')
		return (FORWARD);
	if (key == 's' || key == 'S')
		return (BACKWARD);
	if (key == 'a' || key == 'A')
		return (LEFTWARD);
	if (key == 'd' || key == 'D')
		return (RIGHTWARD);
	if (key == 0xff51)
		return (TURN_LEFT);
	if (key == 0xff53)
		return (TURN_RIGHT);
	return (0);
}

int	key_press(int key, t_game *g)
{
	if (key == 0xff1b)
		return (close_game(g));
	if (!(g->keys & key_mask(key)))
		feature_key(key, g);
	g->keys |= key_mask(key);
	return (0);
}

int	key_release(int key, t_game *g)
{
	g->keys &= ~key_mask(key);
	return (0);
}
