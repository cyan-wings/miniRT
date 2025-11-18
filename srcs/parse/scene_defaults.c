/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_defaults.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/11/19 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

static void	set_default_ambient(t_scene *scene)
{
	scene->ambient.ratio = 0.2;
	scene->ambient.color.r = 255;
	scene->ambient.color.g = 255;
	scene->ambient.color.b = 255;
}

static void	set_default_camera(t_scene *scene)
{
	scene->camera.position = (t_vec3){0, 0, -10};
	scene->camera.direction = (t_vec3){0, 0, 1};
	scene->camera.fov = 60.0;
	scene->camera.scatter_angle = ft_deg_to_rad(DEFAULT_SCATTER_ANGLE);
	scene->camera.rays_per_pixel = DEFAULT_RAYS_PER_PIXEL;
}

static void	set_default_light(t_scene *scene)
{
	scene->light.position = (t_vec3){10, 10, 10};
	scene->light.brightness = 0.8;
	scene->light.color.r = 255;
	scene->light.color.g = 255;
	scene->light.color.b = 255;
}

static int	is_ambient_set(t_ambient *ambient)
{
	return (ambient->ratio != 0.0 || ambient->color.r != 0
		|| ambient->color.g != 0 || ambient->color.b != 0);
}

static int	is_light_set(t_light *light)
{
	return (light->position.x != 0.0 || light->position.y != 0.0
		|| light->position.z != 0.0 || light->brightness != 0.0);
}

void	apply_scene_defaults(t_scene *scene)
{
	if (!is_ambient_set(&scene->ambient))
		set_default_ambient(scene);
	if (scene->camera.fov == 0.0)
		set_default_camera(scene);
	if (!is_light_set(&scene->light))
		set_default_light(scene);
}
