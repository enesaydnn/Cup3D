/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_text_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static char	*bonus_digits(int value)
{
	static char	buf[16];
	long		n;
	int			i;

	n = value;
	if (n < 0)
		n = -n;
	i = 15;
	buf[i--] = '\0';
	while (n || i == 14)
	{
		buf[i--] = '0' + n % 10;
		n /= 10;
	}
	if (value < 0)
		buf[i--] = '-';
	return (&buf[i + 1]);
}

static void	bonus_label(t_game *g, int y, char *label, int value)
{
	int	x;

	x = g->width - 235;
	if (x < 8)
		x = 8;
	mlx_string_put(g->mlx, g->window, x + 8, y, 0xc1d9e5, label);
	mlx_string_put(g->mlx, g->window, x + 147, y, 0xffd585,
		bonus_digits(value));
}

void	bonus_panel(t_game *g)
{
	int	x;
	int	y;
	int	left;

	if (!g->bonus.debug)
		return ;
	left = g->width - 235;
	if (left < 8)
		left = 8;
	y = 8 + g->height / 25;
	while (y < 224 + g->height / 25 && y < g->height)
	{
		x = left - 1;
		while (++x < g->width - 8)
			pixel(&g->frame, x, y, 0x101b29);
		y++;
	}
}

static void	bonus_text_ray(t_game *g, int y, t_ray *ray)
{
	bonus_label(g, y, "Camera x1000", (int)(ray->camera_x * 1000));
	bonus_label(g, y + 14, "Dir X x100", (int)(ray->dx * 100));
	bonus_label(g, y + 28, "Dir Y x100", (int)(ray->dy * 100));
	bonus_label(g, y + 42, "DDA steps", ray->steps);
	bonus_label(g, y + 56, "Trace cells", g->bonus.visible);
	bonus_label(g, y + 70, "Hit X", ray->map_x);
	bonus_label(g, y + 84, "Hit Y", ray->map_y);
	bonus_label(g, y + 98, "Distance x100", (int)(ray->distance * 100));
	bonus_label(g, y + 112, "Side", ray->side);
	bonus_label(g, y + 126, "Door", ray->door);
}

void	bonus_text(t_game *g)
{
	int	y;
	int	shown;

	if (!g->bonus.debug || !g->bonus.rays || !g->window)
		return ;
	y = 23 + g->height / 25;
	shown = g->width / g->bonus.step + (g->width % g->bonus.step != 0);
	shown += (g->bonus.selected % g->bonus.step != 0);
	bonus_label(g, y, "Selected J/K", g->bonus.selected);
	bonus_label(g, y + 14, "Rays cast", g->width);
	bonus_label(g, y + 28, "Rays shown", shown);
	bonus_label(g, y + 42, "Sample [ ]", g->bonus.step);
	bonus_text_ray(g, y + 56, &g->bonus.rays[g->bonus.selected]);
}
