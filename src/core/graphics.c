/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static int	image_address(t_game *g, t_image *img)
{
	img->data = mlx_get_data_addr(img->handle, &img->bpp,
			&img->stride, &img->endian);
	if (!img->data || img->bpp != 32 || img->stride < img->width * 4)
		return (fail(g, "Unsupported image format"));
	return (1);
}

static int	load_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		g->textures[i].handle = mlx_xpm_file_to_image(g->mlx, g->paths[i],
				&g->textures[i].width, &g->textures[i].height);
		if (!g->textures[i].handle || g->textures[i].width <= 0
			|| g->textures[i].height <= 0)
			return (fail(g, "Cannot load XPM texture"));
		if (!image_address(g, &g->textures[i]))
			return (0);
		i++;
	}
	return (1);
}

int	graphics_init(t_game *g)
{
	int	screen_x;
	int	screen_y;

	g->mlx = mlx_init();
	if (!g->mlx)
		return (fail(g, "Cannot initialize MiniLibX display"));
	mlx_get_screen_size(g->mlx, &screen_x, &screen_y);
	g->width = screen_x - screen_x / 4;
	g->height = screen_y - screen_y / 4;
	if (g->width <= 0 || g->height <= 0)
		return (fail(g, "Invalid display size"));
	g->window = mlx_new_window(g->mlx, g->width, g->height, "cub3D");
	if (!g->window || !load_textures(g))
		return (fail(g, "Cannot initialize graphics"));
	g->frame.width = g->width;
	g->frame.height = g->height;
	g->frame.handle = mlx_new_image(g->mlx, g->width, g->height);
	if (!g->frame.handle)
		return (fail(g, "Cannot create frame image"));
	return (image_address(g, &g->frame));
}

void	pixel(t_image *img, int x, int y, int color)
{
	char	*address;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	address = img->data + y * img->stride + x * 4;
	*(unsigned int *)address = (unsigned int)color;
}

int	image_color(t_image *img, int x, int y)
{
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	return (*(unsigned int *)(img->data + y * img->stride + x * 4));
}
