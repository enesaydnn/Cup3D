/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	background(t_game *g)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < g->height)
	{
		color = g->ceil_color;
		if (y >= g->height / 2)
			color = g->floor_color;
		x = 0;
		while (x < g->width)
			pixel(&g->frame, x++, y, color);
		y++;
	}
}

static void	wall_column(t_game *g, t_ray *r, int x)
{
	t_image	*tex;
	int		y;
	int		tex_x;
	int		tex_y;
	double	half;

	if (!r->hit || r->distance <= 0.000001)
		return ;
	tex = &g->textures[r->face];
	tex_x = (int)(r->wall_x * tex->width);
	if ((r->side == 0 && r->dx < 0)
		|| (r->side == 1 && r->dy > 0))
		tex_x = tex->width - tex_x - 1;
	half = g->height / (2.0 * r->distance);
	y = 0;
	if (half < g->height / 2.0)
		y = (int)(g->height / 2.0 - half);
	while (y < g->height && y < g->height / 2.0 + half)
	{
		tex_y = (int)(((y - g->height / 2.0) * r->distance
					/ g->height + 0.5) * tex->height);
		if (tex_y >= 0 && tex_y < tex->height)
			pixel(&g->frame, x, y, image_color(tex, tex_x, tex_y));
		y++;
	}
}

void	render(t_game *g)
{
	t_ray	ray;
	int		x;

	background(g);
	x = 0;
	while (x < g->width)
	{
		cast_ray(g, &ray, x);
		wall_column(g, &ray, x);
		feature_store_ray(g, &ray, x);
		x++;
	}
	feature_draw(g);
	mlx_put_image_to_window(g->mlx, g->window, g->frame.handle, 0, 0);
	feature_text(g);
}
