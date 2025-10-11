/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixel(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_color	trace_ray(t_ray ray, t_scene *scene, int depth)
{
	t_hit	hit;
	t_color	black;
	t_color	local_color;
	t_color	reflected_color;
	t_vec3	reflected_dir;
	t_vec3	reflected_origin;
	t_vec3	offset;
	t_ray	reflected_ray;

	black = (t_color){0, 0, 0};
	if (depth <= 0)
		return (black);
	hit = intersect_scene(ray, scene);
	if (!hit.hit)
		return (black);
	local_color = calculate_lighting(hit, scene, ray);
	reflected_dir = ft_vec3_reflect(ray.direction, hit.normal);
	if (ft_vec3_length(reflected_dir) < EPSILON)
		return (local_color);
	offset = ft_vec3_mult(hit.normal, EPSILON);
	reflected_origin = ft_vec3_add(hit.point, offset);
	reflected_ray = ray_create(reflected_origin, reflected_dir);
	reflected_color = trace_ray(reflected_ray, scene, depth - 1);
	return (color_add(local_color, reflected_color));
}

void	render_scene(t_minirt *minirt)
{
	int		x;
	int		y;
	int		sample;
	int		rpp;
	double	u;
	double	v;
	double	jitter_u;
	double	jitter_v;
	t_ray	ray;
	t_color	pixel_color;
	t_color	sample_color;
	double	inv_samples;
	int		color_int;

	y = 0;
	rpp = minirt->scene.camera.rays_per_pixel;
	if (rpp < 1)
		rpp = 1;
	inv_samples = 1.0 / (double)rpp;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixel_color = (t_color){0, 0, 0};
			sample = 0;
			while (sample < rpp)
			{
				if (rpp == 1)
				{
					jitter_u = 0.5;
					jitter_v = 0.5;
				}
				else
				{
					jitter_u = random_double();
					jitter_v = random_double();
				}
				u = ((double)x + jitter_u) / (WIN_WIDTH - 1);
				v = ((double)(WIN_HEIGHT - 1 - y) + jitter_v) / (WIN_HEIGHT - 1);
				ray = camera_get_ray_scattered(&minirt->scene.camera, u, v,
						jitter_u, jitter_v);
				sample_color = trace_ray(ray, &minirt->scene, MAX_DEPTH);
				pixel_color = color_add(pixel_color, sample_color);
				sample++;
			}
			pixel_color = color_mult(pixel_color, inv_samples);
			color_int = color_to_int(pixel_color);
			put_pixel(&minirt->mlx_data, x, y, color_int);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt->mlx_data.mlx, minirt->mlx_data.win,
		minirt->mlx_data.img, 0, 0);
}