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
	data->oc = ft_vec3_sub(ray->origin, sphere->center);
	data->a = ft_vec3_dot(ray->direction, ray->direction);
	data->b = 2.0 * ft_vec3_dot(data->oc, ray->direction);
	data->c = ft_vec3_dot(data->oc, data->oc)
		- sphere->radius * sphere->radius;
	data->discriminant = data->b * data->b - 4 * data->a * data->c;
}

t_hit	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_hit				hit;
	t_sphere_intersect	data;
	double				sqrtd;
	double				t;

	ft_memset(&hit, 0, sizeof(t_hit));
	init_data(&data, &ray, sphere);
	if (data.discriminant < 0)
		return (hit);
	sqrtd = ft_sqrt(data.discriminant);
	t = (-data.b - sqrtd) / (2.0 * data.a);
	if (t < EPSILON)
	{
		t = (-data.b + sqrtd) / (2.0 * data.a);
		if (t < EPSILON)
			return (hit);
	}
	hit.hit = 1;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = ft_vec3_normalize(ft_vec3_sub(hit.point, sphere->center));
	hit.material = sphere->material;
	return (hit);
}
