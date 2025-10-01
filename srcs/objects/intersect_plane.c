/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	intersect_plane(t_ray ray, t_plane *plane)
{
	t_hit	hit;
	double	denom;
	double	t;
	t_vec3	p0l0;

	ft_memset(&hit, 0, sizeof(t_hit));
	denom = ft_vec3_dot(plane->normal, ray.direction);
	if (ft_abs(denom) < EPSILON)
		return (hit);
	p0l0 = ft_vec3_sub(plane->point, ray.origin);
	t = ft_vec3_dot(p0l0, plane->normal) / denom;
	if (t < EPSILON)
		return (hit);
	hit.hit = 1;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = plane->normal;
	if (ft_vec3_dot(ray.direction, hit.normal) > 0)
		hit.normal = ft_vec3_mult(hit.normal, -1.0);
	hit.material = plane->material;
	return (hit);
}