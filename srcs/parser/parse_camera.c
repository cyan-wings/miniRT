/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_deg_to_rad(double deg);

t_vec3	parse_vector(char *str);

static double	parse_scatter_angle(char *str)
{
	double	scatter;

	scatter = ft_atof(str);
	if (scatter < 0.0)
		scatter = 0.0;
	if (scatter > MAX_SCATTER_ANGLE)
		scatter = MAX_SCATTER_ANGLE;
	return (ft_deg_to_rad(scatter));
}

static int	parse_rays_per_pixel(char *str)
{
	int	rpp;

	rpp = ft_atoi(str);
	if (rpp < 1)
		rpp = DEFAULT_RAYS_PER_PIXEL;
	if (rpp > MAX_RAYS_PER_PIXEL)
		rpp = MAX_RAYS_PER_PIXEL;
	return (rpp);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	scene->camera.position = parse_vector(tokens[1]);
	scene->camera.direction = ft_vec3_normalize(parse_vector(tokens[2]));
	scene->camera.fov = ft_atof(tokens[3]);
	scene->camera.scatter_angle = ft_deg_to_rad(DEFAULT_SCATTER_ANGLE);
	scene->camera.rays_per_pixel = DEFAULT_RAYS_PER_PIXEL;
	if (tokens[4])
		scene->camera.scatter_angle = parse_scatter_angle(tokens[4]);
	if (tokens[4] && tokens[5])
		scene->camera.rays_per_pixel = parse_rays_per_pixel(tokens[5]);
	return (1);
}
