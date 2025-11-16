/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_data(t_sphere_intersect *data, t_ray *ray, t_sphere *sphere)
{
	t_vec3	oc;

	oc = ft_vec3_sub(ray->origin, sphere->center);
	data->a = ft_vec3_dot(ray->direction, ray->direction);
	data->b = 2.0 * ft_vec3_dot(oc, ray->direction);
	data->c = ft_vec3_dot(oc, oc)
		- sphere->radius * sphere->radius;
	data->discriminant = data->b * data->b - 4 * data->a * data->c;
	if (data->discriminant < 0)
		return (0);
	data->sqrtd = ft_sqrt(data->discriminant);
	data->t = (-data->b - data->sqrtd) / (2.0 * data->a);
	if (data->t < EPSILON)
	{
		data->t = (-data->b + data->sqrtd) / (2.0 * data->a);
		if (data->t < EPSILON)
			return (0);
	}
	return (1);
}

// Check on EPSILON usage for min max intersection.
t_hit	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_sphere_intersect	data;
	t_hit				hit;
	t_vec3				outward_normal;

	if (!init_data(&data, &ray, sphere))
		return ((t_hit){});
	ft_memset(&hit, 0, sizeof(t_hit));
	hit.hit = 1;
	hit.t = data.t;
	hit.point = ray_at(ray, data.t);
	outward_normal = ft_vec3_normalize(ft_vec3_sub(hit.point, sphere->center));
	hit.front_face = (ft_vec3_dot(ray.direction, outward_normal) < 0);
	if (hit.front_face)
		hit.normal = outward_normal;
	else
		hit.normal = ft_vec3_mult(outward_normal, -1.0);
	hit.material = sphere->material;
	return (hit);
}
