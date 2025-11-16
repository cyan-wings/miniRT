/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/14 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_cylinder_data(t_cylinder_intersect *d, t_ray *ray,
		t_cylinder *cyl)
{
	t_vec3	oc;
	t_vec3	cross_dir_axis;
	t_vec3	cross_oc_axis;

	ft_memset(d, 0, sizeof(t_cylinder_intersect));
	d->axis_n = ft_vec3_normalize(cyl->axis);
	d->half_h = cyl->height * 0.5;
	oc = ft_vec3_sub(ray->origin, cyl->center);
	cross_dir_axis = ft_vec3_cross(ray->direction, d->axis_n);
	cross_oc_axis = ft_vec3_cross(oc, d->axis_n);
	d->a = ft_vec3_dot(cross_dir_axis, cross_dir_axis);
	d->b = 2.0 * ft_vec3_dot(cross_dir_axis, cross_oc_axis);
	d->c = ft_vec3_dot(cross_oc_axis, cross_oc_axis)
		- (cyl->radius * cyl->radius);
	d->discriminant = d->b * d->b - 4.0 * d->a * d->c;
	ft_memset(&d->best_hit, 0, sizeof(t_hit));
}

static int	check_cylinder_caps_with_axis(t_ray ray, t_cylinder *cyl,
		double t, t_vec3 axis_n)
{
	t_vec3	point;
	t_vec3	to_point;
	double	projection;
	double	half_h;

	point = ray_at(ray, t);
	to_point = ft_vec3_sub(point, cyl->center);
	projection = ft_vec3_dot(to_point, axis_n);
	half_h = cyl->height * 0.5;
	return (projection >= -half_h && projection <= half_h);
}

static t_hit	create_cylinder_side_hit(t_ray ray, t_cylinder *cyl,
		double t, t_vec3 axis_n)
{
	t_hit	hit;
	t_vec3	to_point;
	t_vec3	proj_point;
	double	proj;

	ft_memset(&hit, 0, sizeof(t_hit));
	hit.hit = 1;
	hit.t = t;
	hit.point = ray_at(ray, t);
	to_point = ft_vec3_sub(hit.point, cyl->center);
	proj = ft_vec3_dot(to_point, axis_n);
	proj_point = ft_vec3_add(cyl->center, ft_vec3_mult(axis_n, proj));
	hit.normal = ft_vec3_normalize(ft_vec3_sub(hit.point, proj_point));
	hit.material = cyl->material;
	return (hit);
}

void	intersect_cylinder_caps(t_ray ray, t_cylinder *cyl,
				t_cylinder_intersect *d);

t_hit	intersect_cylinder(t_ray ray, t_cylinder *cyl)
{
	t_cylinder_intersect	d;

	init_cylinder_data(&d, &ray, cyl);
	if (!(d.discriminant < 0.0 || ft_abs(d.a) < EPSILON))
	{
		d.sqrtd = ft_sqrt(d.discriminant);
		d.t_side = (-d.b - d.sqrtd) / (2.0 * d.a);
		if (d.t_side > EPSILON
			&& check_cylinder_caps_with_axis(ray, cyl, d.t_side, d.axis_n))
			d.best_hit = create_cylinder_side_hit(ray, cyl, d.t_side, d.axis_n);
		else
		{
			d.t_side = (-d.b + d.sqrtd) / (2.0 * d.a);
			if (d.t_side > EPSILON
				&& check_cylinder_caps_with_axis(ray, cyl, d.t_side, d.axis_n))
				d.best_hit = create_cylinder_side_hit(ray, cyl, d.t_side,
						d.axis_n);
		}
	}
	intersect_cylinder_caps(ray, cyl, &d);
	return (d.best_hit);
}
