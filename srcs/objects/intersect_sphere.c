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

t_hit	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_hit	hit;
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;

	ft_memset(&hit, 0, sizeof(t_hit));
	oc = ft_vec3_sub(ray.origin, sphere->center);
	a = ft_vec3_dot(ray.direction, ray.direction);
	b = 2.0 * ft_vec3_dot(oc, ray.direction);
	c = ft_vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit);
	t = (-b - ft_sqrt(discriminant)) / (2.0 * a);
	if (t < EPSILON)
	{
		t = (-b + ft_sqrt(discriminant)) / (2.0 * a);
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
