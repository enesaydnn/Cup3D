/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	parser_element(t_game *g, const char *line);
int	parser_map_line(t_game *g, const char *line, int *capacity);

int	parser_open_scene(t_game *g, const char *path)
{
	int	fd;

	if (!path || !str_ends(path, ".cub"))
	{
		fail(g, "Scene must have a .cub extension");
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		fail(g, "Cannot open scene");
	return (fd);
}

int	parser_close_scene(t_game *g, int fd, char *line, int status)
{
	free(line);
	if (close(fd) < 0 && status)
		return (fail(g, "Cannot close scene"));
	return (status);
}

static int	map_phase(t_game *g, const char *line, int *phase, int *capacity)
{
	if (*phase == 1 && *line == '\0')
	{
		*phase = 2;
		return (1);
	}
	if (*phase == 1)
		return (parser_map_line(g, line, capacity));
	if (*line == '\0')
		return (1);
	return (fail(g, "Content after map"));
}

int	parser_process_line(t_game *g, const char *line, int *phase, int *capacity)
{
	const char	*content;
	int			result;

	if (*phase != 0)
		return (map_phase(g, line, phase, capacity));
	content = line;
	while (*content == ' ' || *content == '\t')
		content++;
	if (!*content)
		return (1);
	result = parser_element(g, content);
	if (result != -1)
		return (result);
	if (g->seen != 63u)
		return (fail(g, "Missing or invalid scene element"));
	*phase = 1;
	return (parser_map_line(g, line, capacity));
}
