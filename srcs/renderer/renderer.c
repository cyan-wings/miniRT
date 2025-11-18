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

static void	get_jitters(int rpp, double *jitter_u, double *jitter_v)
{
	if (rpp == 1)
	{
		*jitter_u = 0.5;
		*jitter_v = 0.5;
	}
	else
	{
		*jitter_u = random_double();
		*jitter_v = random_double();
	}
}

t_color	trace_ray(t_ray ray, t_scene *scene, int depth, int max_splits);

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
		get_jitters(rpp, &jitter_u, &jitter_v);
		ray = camera_get_ray_scattered(&scene->camera, camera_base_direction(
					&scene->camera, (x + jitter_u) / (WIN_WIDTH - 1),
					(WIN_HEIGHT - 1.0 - y + jitter_v) / (WIN_HEIGHT - 1)),
				jitter_u, jitter_v);
		pixel_color = color_add(pixel_color, trace_ray(ray, scene, MAX_DEPTH,
					MAX_SPLITS));
	}
	return (color_scale(pixel_color, 1 / (double)rpp));
}

void	render_line(t_minirt *minirt, int y, int rpp)
{
	int		x;
	int		color_int;

	x = 0;
	while (x < WIN_WIDTH)
	{
		color_int = color_to_int(get_pixel_color(rpp, x, y,
					&minirt->scene));
		put_pixel(&minirt->mlx_data, x, y, color_int);
		x++;
	}
}

void	render_scene(t_minirt *minirt)
{
	int		y;
	int		rpp;

	y = 0;
	rpp = minirt->scene.camera.rays_per_pixel;
	if (rpp < 1)
		rpp = 1;
	while (y < WIN_HEIGHT)
	{
		render_line(minirt, y, rpp);
		y++;
	}
	mlx_put_image_to_window(minirt->mlx_data.mlx, minirt->mlx_data.win,
		minirt->mlx_data.img, 0, 0);
}
