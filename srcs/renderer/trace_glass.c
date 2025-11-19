/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_glass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include "minirt.h"

t_color	trace_ray(t_ray ray, t_scene *scene, int depth);

static void	init_trace_glass_vars(t_ray ray, t_hit *hit, t_trc_gls *buf)
{
	buf->attenuation = (t_color){1, 1, 1};
	if (hit->front_face)
		buf->ri = (1.0 / hit->material.data.gls.refractive_index);
	else
		buf->ri = hit->material.data.gls.refractive_index;
	buf->unit_direction = ft_vec3_normalize(ray.direction);
	buf->cos_theta = fmin(ft_vec3_dot(ft_vec3_mult(buf->unit_direction, -1.0),
				hit->normal), 1.0);
	buf->sin_theta = ft_sqrt(1.0 - buf->cos_theta * buf->cos_theta);
}

static t_vec3	apply_fuzz(t_vec3 direction, double fuzz)
{
	t_vec3	fuzzed;

	if (fuzz > EPSILON)
	{
		fuzzed = ft_vec3_add(direction,
				ft_vec3_mult(ft_vec3_random_unit_vector(), fuzz));
		return (ft_vec3_normalize(fuzzed));
	}
	return (direction);
}

static t_color	trace_single_path(t_ray ray, t_hit *hit, t_scene *scene,
	int depth)
{
	t_trc_gls	buf;
	t_vec3		direction;

	init_trace_glass_vars(ray, hit, &buf);
	if (buf.ri * buf.sin_theta > 1.0
		|| schlick_reflectance(buf.cos_theta, buf.ri) > random_double())
	{
		if (!hit->front_face)
			buf.attenuation = (t_color){1, 1, 1};
		direction = ft_vec3_reflect(buf.unit_direction, hit->normal);
	}
	else
	{
		direction = ft_vec3_refract(buf.unit_direction, hit->normal, buf.ri);
		if (ft_vec3_length(direction) < EPSILON)
			direction = ft_vec3_reflect(buf.unit_direction, hit->normal);
	}
	direction = apply_fuzz(direction, hit->material.data.gls.fuzz);
	return (color_multiply(trace_ray(calc_refracted_ray(hit, direction),
				scene, depth - 1), buf.attenuation));
}

static t_color	trace_split_paths(t_ray ray, t_hit *hit, t_scene *scene,
	int depth)
{
	t_trc_gls	buf;
	t_glass_ray	reflect;
	t_glass_ray	refract;
	double		fresnel;

	init_trace_glass_vars(ray, hit, &buf);
	fresnel = schlick_reflectance(buf.cos_theta, buf.ri);
	reflect.dir = ft_vec3_reflect(buf.unit_direction, hit->normal);
	reflect.dir = apply_fuzz(reflect.dir, hit->material.data.gls.fuzz);
	refract.dir = ft_vec3_refract(buf.unit_direction, hit->normal, buf.ri);
	if (ft_vec3_length(refract.dir) < EPSILON)
		refract.dir = reflect.dir;
	refract.dir = apply_fuzz(refract.dir, hit->material.data.gls.fuzz);
	reflect.color = trace_ray(calc_refracted_ray(hit, reflect.dir),
			scene, depth / 2);
	refract.color = trace_ray(calc_refracted_ray(hit, refract.dir),
			scene, depth / 2);
	if (!hit->front_face)
		reflect.color = color_scale(reflect.color, 1.0);
	return (color_multiply(color_add(color_scale(reflect.color, fresnel),
				color_scale(refract.color, 1.0 - fresnel)), buf.attenuation));
}

t_color	trace_glass(t_ray ray, t_hit hit, t_scene *scene, int depth)
{
	t_trc_gls	buf;

	init_trace_glass_vars(ray, &hit, &buf);
	if (buf.ri * buf.sin_theta > 1.0)
		return (trace_single_path(ray, &hit, scene, depth));
	return (trace_split_paths(ray, &hit, scene, depth));
}
