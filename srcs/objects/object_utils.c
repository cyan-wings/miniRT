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

t_material	material_create(t_color color, double ambient, 
	double diffuse, double specular, double shininess)
{
	t_material	material;

	material.color = color;
	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
	return (material);
}