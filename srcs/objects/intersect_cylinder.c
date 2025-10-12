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
	projection_point = ft_vec3_add(cyl->center,
			ft_vec3_mult(cyl->axis, projection));
	hit.normal = ft_vec3_normalize(ft_vec3_sub(hit.point, projection_point));
	hit.material = cyl->material;
	return (hit);
}

static void	init_data(t_sphere_intersect *data, t_ray *ray,
	t_cylinder *cylinder)
{
	t_vec3	cross_dir_axis;
	t_vec3	cross_oc_axis;
	t_vec3	oc;

	oc = ft_vec3_sub(ray->origin, cylinder->center);
	cross_dir_axis = ft_vec3_cross(ray->direction, cylinder->axis);
	cross_oc_axis = ft_vec3_cross(oc, cylinder->axis);
	data->a = ft_vec3_dot(cross_dir_axis, cross_dir_axis);
	data->b = 2.0 * ft_vec3_dot(cross_dir_axis, cross_oc_axis);
	data->c = ft_vec3_dot(cross_oc_axis, cross_oc_axis)
		- (cylinder->radius * cylinder->radius);
	data->discriminant = data->b * data->b - 4 * data->a * data->c;
}

t_hit	intersect_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_sphere_intersect	data;

	init_data(&data, &ray, cylinder);
	if (data.discriminant < 0 || ft_abs(data.a) < EPSILON)
		return ((t_hit){});
	data.sqrtd = ft_sqrt(data.discriminant);
	data.t = (-data.b - data.sqrtd) / (2.0 * data.a);
	if (data.t < EPSILON || !check_cylinder_caps(ray, cylinder, data.t))
	{
		data.t = (-data.b + data.sqrtd) / (2.0 * data.a);
		if (data.t < EPSILON || !check_cylinder_caps(ray, cylinder, data.t))
			return ((t_hit){});
	}
	return (create_cylinder_hit(ray, cylinder, data.t));
}
