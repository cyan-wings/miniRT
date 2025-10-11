/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	parse_vector(char *str);

static t_color	parse_color(char *str)
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

int	parse_ambient(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2])
		return (0);
	scene->ambient.ratio = ft_atof(tokens[1]);
	scene->ambient.color = parse_color(tokens[2]);
	return (1);
}

int	parse_light(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	scene->light.position = parse_vector(tokens[1]);
	scene->light.brightness = ft_atof(tokens[2]);
	scene->light.color = parse_color(tokens[3]);
	return (1);
}
