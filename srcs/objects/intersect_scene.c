/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hit	intersect_object(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, (t_sphere *)obj->data));
	else if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, (t_plane *)obj->data));
	else if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, (t_cylinder *)obj->data));
	return ((t_hit){0});
}

t_hit	intersect_scene(t_ray ray, t_scene *scene)
{
	t_hit		closest_hit;
	t_hit		current_hit;
	double		closest_t;
	int			i;

	ft_memset(&closest_hit, 0, sizeof(t_hit));
	closest_t = INFINITY_F;
	i = 0;
	while (i < scene->object_count)
	{
		current_hit = intersect_object(ray, &scene->objects[i]);
		if (current_hit.hit && current_hit.t < closest_t)
		{
			closest_hit = current_hit;
			closest_t = current_hit.t;
		}
		i++;
	}
	return (closest_hit);
}
