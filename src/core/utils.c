/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	str_ends(const char *s, const char *suffix)
{
	size_t	a;
	size_t	b;

	a = str_len(s);
	b = str_len(suffix);
	if (a <= b)
		return (0);
	while (b)
	{
		if (s[a - 1] != suffix[b - 1])
			return (0);
		a--;
		b--;
	}
	return (1);
}

void	*mem_zero(void *ptr, size_t size)
{
	unsigned char	*bytes;

	bytes = ptr;
	while (size--)
		*bytes++ = 0;
	return (ptr);
}

char	*str_copy_range(const char *s, size_t len)
{
	char	*copy;
	size_t	i;

	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

int	fail(t_game *g, const char *message)
{
	if (!g->error)
		g->error = message;
	return (0);
}
