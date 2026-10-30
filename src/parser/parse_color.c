/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	component(const char **s, int *value)
{
	while (**s == ' ' || **s == '\t')
		(*s)++;
	if (**s < '0' || **s > '9')
		return (0);
	*value = 0;
	while (**s >= '0' && **s <= '9')
	{
		*value = *value * 10 + *(*s)++ - '0';
		if (*value > 255)
			return (0);
	}
	while (**s == ' ' || **s == '\t')
		(*s)++;
	return (1);
}

int	parser_color(t_game *g, const char *s, int id)
{
	int	rgb;
	int	value;
	int	i;

	rgb = 0;
	i = 0;
	while (i < 3)
	{
		if (!component(&s, &value))
			return (fail(g, "Invalid RGB color"));
		rgb = (rgb << 8) | value;
		if (i < 2 && *s++ != ',')
			return (fail(g, "Invalid RGB color"));
		i++;
	}
	if (*s)
		return (fail(g, "Invalid RGB color"));
	if (id == 4)
		g->floor_color = rgb;
	else
		g->ceil_color = rgb;
	return (1);
}
