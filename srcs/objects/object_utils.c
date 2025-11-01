/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	object_add(t_scene *scene, t_object_type type, void *data)
{
	if (scene->object_count >= MAX_OBJECTS)
		return ;
	scene->objects[scene->object_count].type = type;
	scene->objects[scene->object_count].data = data;
	scene->object_count++;
}

void	objects_free(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i].data)
			free(scene->objects[i].data);
		i++;
	}
	scene->object_count = 0;
}

t_material	material_create(
	double ambient,
	double diffuse,
	double specular,
	double shininess
)
{
	t_material	material;

	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
	material.transparency = 0.0;
	material.refractive_index = 1.0;
	material.fuzz = 0.0;
	return (material);
}

t_material	material_create_glass(t_color tint, double refr_idx, double fuzz)
{
	t_material	material;

	material.color = tint;
	material.ambient = 0.0;
	material.diffuse = 0.0;
	material.specular = 0.0;
	material.shininess = 0.0;
	material.transparency = 1.0;
	material.refractive_index = refr_idx;
	material.fuzz = fuzz;
	return (material);
}
