/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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
#include <unistd.h>

static int	report_error(t_game *g)
{
	const char	*message;
	ssize_t		ret;

	message = g->error;
	if (!message)
		message = "Unknown failure";
	ret = write(2, "Error\n", 6);
	ret += write(2, message, str_len(message));
	ret += write(2, "\n", 1);
	(void)ret;
	cleanup(g);
	return (1);
}

static int	focus_out(t_game *g)
{
	g->keys = 0;
	feature_focus(g);
	return (0);
}

static void	install_hooks(t_game *g)
{
	mlx_hook(g->window, 2, 1L << 0, key_press, g);
	mlx_hook(g->window, 3, 1L << 1, key_release, g);
	mlx_hook(g->window, 17, 0, close_game, g);
	mlx_hook(g->window, 10, 1L << 21, focus_out, g);
	feature_hooks(g);
	mlx_loop_hook(g->mlx, loop_frame, g);
}

int	main(int argc, char **argv)
{
	t_game	g;

	mem_zero(&g, sizeof(g));
	if (argc != 2)
		return (fail(&g, "Usage: ./cub3D scene.cub"), report_error(&g));
	if (!parse_scene(&g, argv[1]) || !graphics_init(&g))
		return (report_error(&g));
	if (!feature_init(&g))
		return (fail(&g, "Out of memory for bonus"), report_error(&g));
	mlx_do_key_autorepeatoff(g.mlx);
	gettimeofday(&g.last_time, NULL);
	install_hooks(&g);
	render(&g);
	mlx_loop(g.mlx);
	cleanup(&g);
	return (0);
}
