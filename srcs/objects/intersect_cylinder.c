/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_cylinder_caps(t_ray ray, t_cylinder *cyl, double t)
{
	t_vec3	point;
	t_vec3	to_point;
	double	projection;

	point = ray_at(ray, t);
	to_point = ft_vec3_sub(point, cyl->center);
	projection = ft_vec3_dot(to_point, cyl->axis);
	return (projection >= 0 && projection <= cyl->height);
}

static t_hit	create_cylinder_hit(t_ray ray, t_cylinder *cyl, double t)
{
	t_hit	hit;
	t_vec3	to_point;
	t_vec3	projection_point;
	double	projection;

	ft_memset(&hit, 0, sizeof(t_hit));
	hit.hit = 1;
	hit.t = t;
	hit.point = ray_at(ray, t);
	to_point = ft_vec3_sub(hit.point, cyl->center);
	projection = ft_vec3_dot(to_point, cyl->axis);
	projection_point = ft_vec3_add(cyl->center, ft_vec3_mult(cyl->axis, projection));
	hit.normal = ft_vec3_normalize(ft_vec3_sub(hit.point, projection_point));
	hit.material = cyl->material;
	return (hit);
}

t_hit	intersect_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_hit	hit;
	t_vec3	oc;
	t_vec3	cross_dir_axis;
	t_vec3	cross_oc_axis;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;

	ft_memset(&hit, 0, sizeof(t_hit));
	oc = ft_vec3_sub(ray.origin, cylinder->center);
	cross_dir_axis = ft_vec3_cross(ray.direction, cylinder->axis);
	cross_oc_axis = ft_vec3_cross(oc, cylinder->axis);
	a = ft_vec3_dot(cross_dir_axis, cross_dir_axis);
	b = 2.0 * ft_vec3_dot(cross_dir_axis, cross_oc_axis);
	c = ft_vec3_dot(cross_oc_axis, cross_oc_axis) - 
		(cylinder->radius * cylinder->radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0 || ft_abs(a) < EPSILON)
		return (hit);
	t = (-b - ft_sqrt(discriminant)) / (2.0 * a);
	if (t < EPSILON || !check_cylinder_caps(ray, cylinder, t))
	{
		t = (-b + ft_sqrt(discriminant)) / (2.0 * a);
		if (t < EPSILON || !check_cylinder_caps(ray, cylinder, t))
			return (hit);
	}
	return (create_cylinder_hit(ray, cylinder, t));
}
