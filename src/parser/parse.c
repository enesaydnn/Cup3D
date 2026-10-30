/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int	parser_process_line(t_game *g, const char *line, int *phase, int *capacity);
int	parser_finish_map(t_game *g);
int	parser_open_scene(t_game *g, const char *path);
int	parser_close_scene(t_game *g, int fd, char *line, int status);

#define R_POS 0
#define R_USED 1
#define R_LEN 2
#define R_CAP 3
#define R_BUFFER 0
#define R_LINE 1

static int	read_byte(int fd, char *buffer, size_t state[4])
{
	ssize_t	count;

	if (state[R_POS] == state[R_USED])
	{
		count = read(fd, buffer, 4096);
		if (count < 0)
			return (-2);
		if (count == 0)
			return (-1);
		state[R_USED] = (size_t)count;
		state[R_POS] = 0;
	}
	return ((unsigned char)buffer[state[R_POS]++]);
}

static int	append_byte(t_game *g, char **memory, size_t state[4], char c)
{
	char	*next;
	char	*dst;
	char	*src;

	if (state[R_LEN] >= INT_MAX - 1)
		return (fail(g, "Scene line is too long"));
	if (state[R_LEN] + 1 >= state[R_CAP])
	{
		state[R_CAP] *= 2;
		if (state[R_CAP] > INT_MAX)
			state[R_CAP] = INT_MAX;
		next = malloc(state[R_CAP]);
		if (!next)
			return (fail(g, "Out of memory"));
		dst = next;
		src = memory[R_LINE];
		while (src < memory[R_LINE] + state[R_LEN])
			*dst++ = *src++;
		free(memory[R_LINE]);
		memory[R_LINE] = next;
	}
	memory[R_LINE][state[R_LEN]++] = c;
	return (1);
}

static int	read_line(t_game *g, int fd, char **memory, size_t state[4])
{
	int	c;

	state[R_LEN] = 0;
	while (1)
	{
		c = read_byte(fd, memory[R_BUFFER], state);
		if (c == -2 || c == 0)
		{
			fail(g, "Failed to read scene");
			return (-1);
		}
		if (c == -1 || c == '\n')
			break ;
		if (!append_byte(g, memory, state, (char)c))
			return (-1);
	}
	memory[R_LINE][state[R_LEN]] = '\0';
	if (c == -1 && state[R_LEN] == 0)
		return (0);
	return (1);
}

static int	parse_stream(t_game *g, int fd, char **memory, size_t state[4])
{
	int	status;
	int	phase;
	int	capacity;

	phase = 0;
	capacity = 0;
	status = 1;
	while (status > 0)
	{
		status = read_line(g, fd, memory, state);
		if (status > 0 && !parser_process_line(g, memory[R_LINE],
				&phase, &capacity))
			return (0);
	}
	if (status < 0)
		return (0);
	if (g->seen != 63u)
		return (fail(g, "Missing scene element"));
	if (g->map.height == 0)
		return (fail(g, "Missing map"));
	return (1);
}

int	parse_scene(t_game *g, const char *path)
{
	char	buffer[4096];
	char	*memory[2];
	size_t	state[4];
	int		fd;
	int		status;

	mem_zero(state, sizeof(state));
	fd = parser_open_scene(g, path);
	if (fd < 0)
		return (0);
	state[R_CAP] = 128;
	memory[R_BUFFER] = buffer;
	memory[R_LINE] = malloc(state[R_CAP]);
	if (!memory[R_LINE])
	{
		close(fd);
		return (fail(g, "Out of memory"));
	}
	status = parse_stream(g, fd, memory, state);
	if (!parser_close_scene(g, fd, memory[R_LINE], status))
		return (0);
	return (parser_finish_map(g));
}
