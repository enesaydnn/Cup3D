/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
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

int	parser_color(t_game *g, const char *value, int id);

static int	identifier(const char *s)
{
	if (s[0] == 'N' && s[1] == 'O' && (s[2] == ' ' || s[2] == '\t'))
		return (NORTH);
	if (s[0] == 'S' && s[1] == 'O' && (s[2] == ' ' || s[2] == '\t'))
		return (SOUTH);
	if (s[0] == 'W' && s[1] == 'E' && (s[2] == ' ' || s[2] == '\t'))
		return (WEST);
	if (s[0] == 'E' && s[1] == 'A' && (s[2] == ' ' || s[2] == '\t'))
		return (EAST);
	if (s[0] == 'F' && (s[1] == ' ' || s[1] == '\t'))
		return (4);
	if (s[0] == 'C' && (s[1] == ' ' || s[1] == '\t'))
		return (5);
	return (-1);
}

static int	check_texture(t_game *g, const char *path)
{
	int		fd;
	int		count;
	char	byte;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (fail(g, "Cannot open texture"));
	count = read(fd, &byte, 1);
	if (close(fd) < 0 || count <= 0)
		return (fail(g, "Cannot read texture"));
	return (1);
}

static int	parse_texture(t_game *g, const char *s, int id)
{
	const char	*start;

	while (*s == ' ' || *s == '\t')
		s++;
	start = s;
	while (*s && *s != ' ' && *s != '\t')
		s++;
	if (s == start)
		return (fail(g, "Empty texture path"));
	g->paths[id] = str_copy_range(start, (size_t)(s - start));
	if (!g->paths[id])
		return (fail(g, "Out of memory"));
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s)
		return (fail(g, "Invalid texture path"));
	return (check_texture(g, g->paths[id]));
}

int	parser_element(t_game *g, const char *line)
{
	int	id;

	id = identifier(line);
	if (id < 0)
		return (-1);
	if (g->seen & (1u << id))
		return (fail(g, "Duplicate scene element"));
	if (id < 4 && !parse_texture(g, line + 2, id))
		return (0);
	if (id >= 4 && !parser_color(g, line + 1, id))
		return (0);
	g->seen |= 1u << id;
	return (1);
}
