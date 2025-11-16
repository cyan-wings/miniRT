/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/14 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cylinder_caps(t_ray ray, t_cylinder *cyl,
				t_cylinder_intersect *d)
{
	d->top_cap_center = ft_vec3_add(
			cyl->center,
			ft_vec3_mult(d->axis_n, d->half_h));
	d->btm_cap_center = ft_vec3_sub(
			cyl->center,
			ft_vec3_mult(d->axis_n, d->half_h));
	d->t_top_cap = ft_vec3_dot(
			ft_vec3_sub(d->top_cap_center, ray.origin),
			d->axis_n)
		/ d->denom;
	d->t_btm_cap = ft_vec3_dot(
			ft_vec3_sub(d->btm_cap_center, ray.origin),
			d->axis_n)
		/ d->denom;
}

static t_hit	create_cylinder_cap_hit(t_ray ray, t_cylinder *cyl,
		double t, int top)
{
	t_hit	hit;
	t_vec3	norm;

	ft_memset(&hit, 0, sizeof(t_hit));
	hit.hit = 1;
	hit.t = t;
	hit.point = ray_at(ray, t);
	norm = ft_vec3_normalize(cyl->axis);
	if (top < 0)
		norm = ft_vec3_mult(norm, -1.0);
	hit.normal = norm;
	hit.material = cyl->material;
	return (hit);
}

static void	intersect_top_cap(t_ray ray, t_cylinder *cyl,
				t_cylinder_intersect *d)
{
	t_vec3	p;
	double	dist;

	if (d->t_top_cap > EPSILON)
	{
		p = ray_at(ray, d->t_top_cap);
		dist = ft_vec3_length(ft_vec3_sub(p, d->top_cap_center));
		if (dist <= cyl->radius + EPSILON
			&& (!d->best_hit.hit || d->t_top_cap < d->best_hit.t))
			d->best_hit = create_cylinder_cap_hit(ray, cyl, d->t_top_cap, 1);
	}
}

static void	intersect_btm_cap(t_ray ray, t_cylinder *cyl,
				t_cylinder_intersect *d)
{
	t_vec3	p;
	double	dist;

	if (d->t_btm_cap > EPSILON)
	{
		p = ray_at(ray, d->t_btm_cap);
		dist = ft_vec3_length(ft_vec3_sub(p, d->btm_cap_center));
		if (dist <= cyl->radius + EPSILON
			&& (!d->best_hit.hit || d->t_btm_cap < d->best_hit.t))
			d->best_hit = create_cylinder_cap_hit(ray, cyl, d->t_btm_cap, -1);
	}
}

void	intersect_cylinder_caps(t_ray ray, t_cylinder *cyl,
				t_cylinder_intersect *d)
{
	d->denom = ft_vec3_dot(ray.direction, d->axis_n);
	if (ft_abs(d->denom) < EPSILON)
		return ;
	init_cylinder_caps(ray, cyl, d);
	intersect_top_cap(ray, cyl, d);
	intersect_btm_cap(ray, cyl, d);
}
