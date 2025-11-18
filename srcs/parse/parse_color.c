/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_error(int set, int value)
{
	static int	error = 0;

	if (set)
		error = value;
	return (error);
}

static int	validate_rgb(int rgb[3])
{
	return (rgb[0] >= 0 && rgb[0] <= 255
		&& rgb[1] >= 0 && rgb[1] <= 255
		&& rgb[2] >= 0 && rgb[2] <= 255);
}

static t_color get_color(int r, int g, int b)
{
	t_color color;

	color.r = r / 255.0;
	color.g = g / 255.0;
	color.b = b / 255.0;
	return (color);
}

t_color	parse_color(char *str)
{
	char	**components;
	t_color	color;
	int		rgb[3];

	components = ft_split(str, ',');
	if (!components)
	{
		parse_error(1, 1);
		return ((t_color){0, 0, 0});
	}
	if (!components[0] || !components[1] || !components[2])
	{
		ft_free_array((void **)components);
		parse_error(1, 1);
		return ((t_color){0, 0, 0});
	}
	rgb[0] = ft_atoi(components[0]);
	rgb[1] = ft_atoi(components[1]);
	rgb[2] = ft_atoi(components[2]);
	ft_free_array((void **)components);
	if (!validate_rgb(rgb))
	{
		parse_error(1, 1);
		return ((t_color){0, 0, 0});
	}
	color = get_color(rgb[0], rgb[1], rgb[2]);
	return (color);
}
