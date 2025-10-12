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

static t_ray	calc_reflected_ray(t_hit *hit, t_vec3 reflected_dir)
{
	t_vec3	offset;
	t_vec3	reflected_origin;

	offset = ft_vec3_mult(hit->normal, EPSILON);
	reflected_origin = ft_vec3_add(hit->point, offset);
	return (ray_create(reflected_origin, reflected_dir));
}

static t_color	trace_ray(t_ray ray, t_scene *scene, int depth)
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
	local_color = calculate_lighting(hit, scene, ray);
	reflected_dir = ft_vec3_reflect(ray.direction, hit.normal);
	if (ft_vec3_length(reflected_dir) < EPSILON)
		return (local_color);
	reflected_color = trace_ray(calc_reflected_ray(&hit, reflected_dir),
			scene, depth - 1);
	return (color_add(local_color, reflected_color));
}

static t_color	get_pixel_color(int rpp, int x, int y, t_scene *scene)
{
	int		sample;
	t_color	pixel_color;
	double	jitter_u;
	double	jitter_v;
	t_ray	ray;

	sample = -1;
	pixel_color = (t_color){0, 0, 0};
	while (++sample < rpp)
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
		ray = camera_get_ray_scattered(&scene->camera, x, y,
				jitter_u, jitter_v);
		pixel_color = color_add(pixel_color, trace_ray(ray, scene, MAX_DEPTH));
	}
	return (pixel_color);
}

void	render_scene(t_minirt *minirt)
{
	int		x;
	int		y;
	int		rpp;
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
			color_int = color_to_int(color_mult(get_pixel_color(rpp, x, y,
							&minirt->scene), inv_samples));
			put_pixel(&minirt->mlx_data, x, y, color_int);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt->mlx_data.mlx, minirt->mlx_data.win,
		minirt->mlx_data.img, 0, 0);
}
