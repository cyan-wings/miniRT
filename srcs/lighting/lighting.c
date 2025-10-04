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

t_color	ambient_light(t_material material, t_ambient ambient)
{
	return (color_multiply(material.color, 
		color_mult(ambient.color, ambient.ratio)));
}

t_color	diffuse_light(t_vec3 light_dir, t_vec3 normal, 
	t_material material, t_color light_color)
{
	double	dot_product;
	t_color	diffuse;

	dot_product = ft_vec3_dot(normal, light_dir);
	if (dot_product < 0)
		dot_product = 0;
	diffuse = color_mult(light_color, material.diffuse * dot_product);
	return (color_multiply(material.color, diffuse));
}

t_color	specular_light(t_vec3 light_dir, t_vec3 view_dir, 
	t_vec3 normal, t_material material, t_color light_color)
{
	t_vec3	reflect_dir;
	double	spec;

	reflect_dir = ft_vec3_reflect(ft_vec3_mult(light_dir, -1.0), normal);
	spec = ft_vec3_dot(view_dir, reflect_dir);
	if (spec < 0)
		spec = 0;
	spec = ft_power(spec, material.shininess);
	return (color_mult(light_color, material.specular * spec));
}

static int	is_in_shadow(t_vec3 point, t_vec3 light_pos, t_scene *scene)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	double	light_distance;
	t_vec3	to_light;

	to_light = ft_vec3_sub(light_pos, point);
	light_distance = ft_vec3_length(to_light);
	shadow_ray = ray_create(ft_vec3_add(point, ft_vec3_mult(to_light, EPSILON)), 
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
	light_dir = ft_vec3_normalize(ft_vec3_sub(scene->light.position, hit.point));
	view_dir = ft_vec3_normalize(ft_vec3_mult(ray.direction, -1.0));
	diffuse_color = diffuse_light(light_dir, hit.normal, 
		hit.material, scene->light.color);
	specular_color = specular_light(light_dir, view_dir, hit.normal, 
		hit.material, scene->light.color);
	final_color = color_add(final_color, 
		color_mult(diffuse_color, scene->light.brightness));
	final_color = color_add(final_color, 
		color_mult(specular_color, scene->light.brightness));
	return (final_color);
}