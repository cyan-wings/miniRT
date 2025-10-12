/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
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

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->center = parse_vector(tokens[1]);
	sphere->radius = ft_atof(tokens[2]) / 2.0;
	sphere->material = material_create(0.1, 0.9, 0.9, 32);
	sphere->material.color = parse_color(tokens[3]);
	object_add(scene, OBJ_SPHERE, sphere);
	return (1);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		*plane;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	plane = ft_memalloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->point = parse_vector(tokens[1]);
	plane->normal = ft_vec3_normalize(parse_vector(tokens[2]));
	plane->material = material_create(0.1, 0.9, 0.0, 0);
	plane->material.color = parse_color(tokens[3]);
	object_add(scene, OBJ_PLANE, plane);
	return (1);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		return (0);
	cylinder = ft_memalloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->center = parse_vector(tokens[1]);
	cylinder->axis = ft_vec3_normalize(parse_vector(tokens[2]));
	cylinder->radius = ft_atof(tokens[3]) / 2.0;
	cylinder->height = ft_atof(tokens[4]);
	cylinder->material = material_create(0.1, 0.9, 0.2, 16);
	cylinder->material.color = parse_color(tokens[5]);
	object_add(scene, OBJ_CYLINDER, cylinder);
	return (1);
}
