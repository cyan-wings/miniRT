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

double	ft_deg_to_rad(double deg);

static void	camera_init_helper(t_camera *camera)
{
	double	max_scatter;

	if (camera->scatter_angle < 0.0)
		camera->scatter_angle = 0.0;
	max_scatter = ft_deg_to_rad(MAX_SCATTER_ANGLE);
	if (camera->scatter_angle > max_scatter)
		camera->scatter_angle = max_scatter;
	if (camera->rays_per_pixel < 1)
		camera->rays_per_pixel = DEFAULT_RAYS_PER_PIXEL;
	if (camera->rays_per_pixel > MAX_RAYS_PER_PIXEL)
		camera->rays_per_pixel = MAX_RAYS_PER_PIXEL;
}

void	camera_init(t_camera *camera)
{
	t_vec3	world_up;
	double	theta;
	double	half_height;
	double	half_width;

	camera->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	theta = ft_deg_to_rad(camera->fov);
	half_height = tan(theta / 2.0);
	half_width = camera->aspect_ratio * half_height;
	camera->viewport_height = 2.0 * half_height;
	camera->viewport_width = 2.0 * half_width;
	world_up = (t_vec3){0, 1, 0};
	camera->right = ft_vec3_normalize(ft_vec3_cross(camera->direction,
				world_up));
	if (ft_vec3_length(camera->right) < EPSILON)
	{
		world_up = (t_vec3){0, 0, 1};
		camera->right = ft_vec3_normalize(ft_vec3_cross(camera->direction,
					world_up));
	}
	camera->up = ft_vec3_normalize(ft_vec3_cross(camera->right,
				camera->direction));
	camera_init_helper(camera);
}

t_vec3	camera_base_direction(t_camera *camera, double u, double v)
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
	return (ft_vec3_sub(direction, camera->position));
}

t_ray	camera_get_ray_scattered(t_camera *camera, t_vec3 direction,
	double jitter_u, double jitter_v)
{
	t_vec3	offset;
	double	angle_x;
	double	angle_y;
	double	signed_u;
	double	signed_v;

	if (camera->scatter_angle > 0.0)
	{
		signed_u = (2.0 * jitter_u) - 1.0;
		signed_v = (2.0 * jitter_v) - 1.0;
		angle_x = camera->scatter_angle * signed_u;
		angle_y = camera->scatter_angle * signed_v;
		offset = ft_vec3_add(ft_vec3_mult(camera->right, tan(angle_x)),
				ft_vec3_mult(camera->up, tan(angle_y)));
		direction = ft_vec3_add(direction, offset);
	}
	return (ray_create(camera->position, direction));
}
