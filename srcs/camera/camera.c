/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_init(t_camera *camera)
{
	t_vec3	world_up;
	double	theta;
	double	half_height;
	double	half_width;

	camera->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	theta = degrees_to_radians(camera->fov);
	half_height = tan(theta / 2.0);
	half_width = camera->aspect_ratio * half_height;
	camera->viewport_height = 2.0 * half_height;
	camera->viewport_width = 2.0 * half_width;
	world_up = (t_vec3){0, 1, 0};
	camera->right = ft_vec3_normalize(ft_vec3_cross(camera->direction, world_up));
	camera->up = ft_vec3_cross(camera->right, camera->direction);
}

t_ray	camera_get_ray(t_camera *camera, double u, double v)
{
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	lower_left;
	t_vec3	direction;

	horizontal = ft_vec3_mult(camera->right, camera->viewport_width);
	vertical = ft_vec3_mult(camera->up, camera->viewport_height);
	lower_left = ft_vec3_sub(camera->position, ft_vec3_div(horizontal, 2.0));
	lower_left = ft_vec3_sub(lower_left, ft_vec3_div(vertical, 2.0));
	lower_left = ft_vec3_add(lower_left, camera->direction);
	direction = ft_vec3_add(lower_left, ft_vec3_mult(horizontal, u));
	direction = ft_vec3_add(direction, ft_vec3_mult(vertical, v));
	direction = ft_vec3_sub(direction, camera->position);
	return (ray_create(camera->position, direction));
}