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

t_color	trace_ray(t_ray ray, t_scene *scene, int depth, int max_splits);

t_color	calculate_lighting(t_hit *hit, t_scene *scene, t_ray ray);

t_ray	calc_reflected_ray(t_hit *hit, t_vec3 reflected_dir);

//	return (color_add(
//		local_color,
//		color_multiply(color_clamp(reflected_color, 0, 1),
//		hit.material.color)));
//	return (color_add(
//		color_scale(local_color, (1.0 - hit.material.shininess)),
//		color_scale(reflected_color, hit.material.shininess)));
t_color	trace_ray(t_ray ray, t_scene *scene, int depth, int max_splits)
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
		return (trace_glass(ray, hit, scene, depth, max_splits));
	local_color = calculate_lighting(&hit, scene, ray);
	reflected_dir = ft_vec3_reflect(ray.direction, hit.normal);
	if (ft_vec3_length(reflected_dir) < EPSILON)
		return (local_color);
	reflected_color = trace_ray(calc_reflected_ray(&hit, reflected_dir),
			scene, depth - 1, max_splits);
	return (color_add(
			local_color,
			color_scale(color_multiply(reflected_color, hit.material.color),
				0.5)));
}
