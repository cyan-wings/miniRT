/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = ft_vec3_normalize(direction);
	return (ray);
}

t_vec3	ray_at(t_ray ray, double t)
{
	return (ft_vec3_add(ray.origin, ft_vec3_mult(ray.direction, t)));
}

t_ray	calc_reflected_ray(t_hit *hit, t_vec3 reflected_dir)
{
	t_vec3	offset;
	t_vec3	reflected_origin;

	offset = ft_vec3_mult(hit->normal, EPSILON);
	reflected_origin = ft_vec3_add(hit->point, offset);
	return (ray_create(reflected_origin, reflected_dir));
}

// Offset in the direction of the ray to avoid self-intersection
// This works for both reflection and refraction
t_ray	calc_refracted_ray(t_hit *hit, t_vec3 direction)
{
	t_vec3	offset;
	t_vec3	origin;

	offset = ft_vec3_mult(ft_vec3_normalize(hit->normal), EPSILON);
	origin = ft_vec3_sub(hit->point, offset);
	return (ray_create(origin, direction));
}

double	schlick_reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0));
}
