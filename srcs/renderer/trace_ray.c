/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include "minirt.h"

t_hit	intersect_scene(t_ray ray, t_scene *scene);

t_color	trace_ray(t_ray ray, t_scene *scene, int depth);

static void	init_trace_glass_vars(t_ray ray, t_hit *hit, t_trc_gls *buf)
{
	buf->attenuation = hit->material.color;
	if (hit->front_face)
		buf->ri = (1.0 / hit->material.data.gls.refractive_index);
	else
		buf->ri = hit->material.data.gls.refractive_index;
	buf->unit_direction = ft_vec3_normalize(ray.direction);
	buf->cos_theta = fmin(ft_vec3_dot(ft_vec3_mult(buf->unit_direction, -1.0),
				hit->normal), 1.0);
	buf->sin_theta = ft_sqrt(1.0 - buf->cos_theta * buf->cos_theta);
}

static t_color	trace_glass(t_ray ray, t_hit hit, t_scene *scene, int depth)
{
	t_trc_gls	buf;
	t_vec3		direction;

	init_trace_glass_vars(ray, &hit, &buf);
	if (buf.ri * buf.sin_theta > 1.0
		|| schlick_reflectance(buf.cos_theta, buf.ri) > random_double())
	{
		if (!hit.front_face)
			buf.attenuation = (t_color){1, 1, 1};
		direction = ft_vec3_reflect(buf.unit_direction, hit.normal);
	}
	else
	{
		direction = ft_vec3_refract(buf.unit_direction, hit.normal, buf.ri);
		if (ft_vec3_length(direction) < EPSILON)
			direction = ft_vec3_reflect(buf.unit_direction, hit.normal);
	}
	if (hit.material.data.gls.fuzz > EPSILON)
		direction = ft_vec3_add(direction,
				ft_vec3_mult(ft_vec3_random_unit_vector(),
					hit.material.data.gls.fuzz));
	direction = ft_vec3_normalize(direction);
	return (color_multiply(trace_ray(calc_refracted_ray(&hit, direction),
				scene, depth - 1), buf.attenuation));
}

t_color	calculate_lighting(t_hit *hit, t_scene *scene, t_ray ray);

t_ray	calc_reflected_ray(t_hit *hit, t_vec3 reflected_dir);

//	return (color_add(
//		local_color,
//		color_multiply(color_clamp(reflected_color, 0, 1),
//		hit.material.color)));
//	return (color_add(
//		color_scale(local_color, (1.0 - hit.material.shininess)),
//		color_scale(reflected_color, hit.material.shininess)));
t_color	trace_ray(t_ray ray, t_scene *scene, int depth)
{
	t_hit	hit;
	t_color	local_color;
	t_vec3	reflected_dir;
	t_color	reflected_color;

	if (depth <= 0)
		return ((t_color){0, 0, 0});
	hit = intersect_scene(ray, scene);
	if (!hit.hit)
		return ((t_color){0, 0, 0});
	if (hit.material.type == GLASS)
		return (trace_glass(ray, hit, scene, depth));
	local_color = calculate_lighting(&hit, scene, ray);
	reflected_dir = ft_vec3_reflect(ray.direction, hit.normal);
	if (ft_vec3_length(reflected_dir) < EPSILON)
		return (local_color);
	reflected_color = trace_ray(calc_reflected_ray(&hit, reflected_dir),
			scene, depth - 1);
	return (color_add(
			local_color,
			color_scale(color_multiply(reflected_color, hit.material.color),
				0.5)));
}
