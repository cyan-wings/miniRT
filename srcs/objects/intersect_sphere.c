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

static void	init_data(t_sphere_intersect *data, t_ray *ray, t_sphere *sphere)
{
	t_vec3	oc;

	oc = ft_vec3_sub(ray->origin, sphere->center);
	data->a = ft_vec3_dot(ray->direction, ray->direction);
	data->b = 2.0 * ft_vec3_dot(oc, ray->direction);
	data->c = ft_vec3_dot(oc, oc)
		- sphere->radius * sphere->radius;
	data->discriminant = data->b * data->b - 4 * data->a * data->c;
}

// Check on EPSILON usage for min max intersection.
t_hit	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_sphere_intersect	data;
	t_hit				hit;

	init_data(&data, &ray, sphere);
	if (data.discriminant < 0)
		return ((t_hit){});
	data.sqrtd = ft_sqrt(data.discriminant);
	data.t = (-data.b - data.sqrtd) / (2.0 * data.a);
	if (data.t < EPSILON)
	{
		data.t = (-data.b + data.sqrtd) / (2.0 * data.a);
		if (data.t < EPSILON)
			return ((t_hit){});
	}
	ft_memset(&hit, 0, sizeof(t_hit));
	hit.hit = 1;
	hit.t = data.t;
	hit.point = ray_at(ray, data.t);
	hit.normal = ft_vec3_normalize(ft_vec3_sub(hit.point, sphere->center));
	hit.material = sphere->material;
	return (hit);
}
