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

t_color	parse_color(char *str)
{
	char	**components;
	t_color	color;

	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		if (components)
			ft_free_array((void **)components);
		return ((t_color){0, 0, 0});
	}
	color.r = ft_atoi(components[0]) / 255.0;
	color.g = ft_atoi(components[1]) / 255.0;
	color.b = ft_atoi(components[2]) / 255.0;
	ft_free_array((void **)components);
	return (color);
}
