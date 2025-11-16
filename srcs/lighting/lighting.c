/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	ambient_light(t_material material, t_ambient ambient)
{
	return (color_multiply(material.color,
			color_scale(ambient.color, ambient.ratio)));
}

static t_color	diffuse_light(
	t_vec3 light_dir,
	t_vec3 normal,
	t_material material,
	t_color light_color
)
{
	double	dot_product;
	t_color	diffuse;

	dot_product = ft_vec3_dot(normal, light_dir);
	if (dot_product < 0)
		dot_product = 0;
	diffuse = color_scale(light_color, material.diffuse * dot_product);
	return (color_multiply(material.color, diffuse));
}

/*
	1. Starting from the light source shooting a ray onto any surface.
	2. The ray reflection off the surface is calculated and stored in
		light_reflected_dir.
	3. specular_angle_factor is the dot product of camera view and the 
		incoming light ray. Negative means the ray is not the same direction,
		so the image should not take into account.
	4. Then specular_intensity is calculated by taking power of the
		specular_angle_factor to the surface shineness.

	A light ray that is shone in a direction can be imagined as a torchlight.
	The center of the light source is the most intense while surrounding it
	gets less intense when away from the center.
	
	specular_angle_factor of 1 indicates highest intensity from the light ray
	as it is shone directly into the camera view. Hence, colour should be
	very intense.

	Shininess amplifies the light ray that bounces off.
*/
static double	calc_specular_intensity(
	t_vec3 light_dir,
	t_vec3 normal,
	t_vec3 view_dir,
	double material_shininess
)
{
	t_vec3	light_reflected_dir;
	double	specular_angle_factor;

	light_reflected_dir = ft_vec3_reflect(
			ft_vec3_mult(light_dir, -1.0),
			normal);
	specular_angle_factor = ft_vec3_dot(view_dir, light_reflected_dir);
	if (specular_angle_factor < 0)
		return (0);
	return (ft_power(specular_angle_factor, material_shininess));
}

static int	is_in_shadow(t_vec3 point, t_vec3 light_pos, t_scene *scene)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	double	light_distance;
	t_vec3	to_light;

	to_light = ft_vec3_sub(light_pos, point);
	light_distance = ft_vec3_length(to_light);
	shadow_ray = ray_create(ft_vec3_add(
				point,
				ft_vec3_mult(to_light, EPSILON)
				),
			ft_vec3_normalize(to_light));
	shadow_hit = intersect_scene(shadow_ray, scene);
	return (shadow_hit.hit && shadow_hit.t < light_distance);
}

t_color	calculate_lighting(t_hit hit, t_scene *scene, t_ray ray)
{
	t_color	final_color;
	t_color	diffuse_color;
	t_color	specular_color;
	t_vec3	light_dir;
	t_vec3	view_dir;

	final_color = ambient_light(hit.material, scene->ambient);
	if (is_in_shadow(hit.point, scene->light.position, scene))
		return (final_color);
	light_dir = ft_vec3_normalize(
			ft_vec3_sub(scene->light.position, hit.point));
	view_dir = ft_vec3_normalize(ft_vec3_mult(ray.direction, -1.0));
	diffuse_color = diffuse_light(light_dir, hit.normal,
			hit.material, scene->light.color);
	specular_color = color_scale(scene->light.color,
			hit.material.specular * calc_specular_intensity(
				light_dir, hit.normal, view_dir, hit.material.shininess));
	final_color = color_add(final_color,
			color_scale(diffuse_color, scene->light.brightness));
	final_color = color_add(final_color,
			color_scale(specular_color, scene->light.brightness));
	return (final_color);
}
