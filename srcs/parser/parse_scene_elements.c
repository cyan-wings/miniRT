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

static t_vec3	parse_vector(char *str)
{
	char	**components;
	t_vec3	vec;

	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		if (components)
			ft_free_array((void **)components);
		return ((t_vec3){0, 0, 0});
	}
	vec.x = ft_atof(components[0]);
	vec.y = ft_atof(components[1]);
	vec.z = ft_atof(components[2]);
	ft_free_array((void **)components);
	return (vec);
}

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

int	parse_ambient(char **tokens, t_ambient *ambient)
{
	if (!tokens[1] || !tokens[2])
		return (0);
	ambient->ratio = ft_atof(tokens[1]);
	ambient->color = parse_color(tokens[2]);
	return (1);
}

int	parse_camera(char **tokens, t_camera *camera)
{
	double	scatter;
	int		rpp;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	camera->position = parse_vector(tokens[1]);
	camera->direction = ft_vec3_normalize(parse_vector(tokens[2]));
	camera->fov = ft_atof(tokens[3]);
	camera->scatter_angle = degrees_to_radians(DEFAULT_SCATTER_ANGLE);
	camera->rays_per_pixel = DEFAULT_RAYS_PER_PIXEL;
	if (tokens[4])
	{
		scatter = ft_atof(tokens[4]);
		if (scatter < 0.0)
			scatter = 0.0;
		if (scatter > MAX_SCATTER_ANGLE)
			scatter = MAX_SCATTER_ANGLE;
		camera->scatter_angle = degrees_to_radians(scatter);
	}
	if (tokens[4] && tokens[5])
	{
		rpp = ft_atoi(tokens[5]);
		if (rpp < 1)
			rpp = DEFAULT_RAYS_PER_PIXEL;
		if (rpp > MAX_RAYS_PER_PIXEL)
			rpp = MAX_RAYS_PER_PIXEL;
		camera->rays_per_pixel = rpp;
	}
	return (1);
}

int	parse_light(char **tokens, t_light *light)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	light->position = parse_vector(tokens[1]);
	light->brightness = ft_atof(tokens[2]);
	light->color = parse_color(tokens[3]);
	return (1);
}