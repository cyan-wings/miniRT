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

	black = (t_color){0, 0, 0};
	if (depth <= 0)
		return (black);
	hit = intersect_scene(ray, scene);
	if (!hit.hit)
		return (black);
	return (calculate_lighting(hit, scene, ray));
}

void	render_scene(t_minirt *minirt)
{
	int		x;
	int		y;
	double	u;
	double	v;
	t_ray	ray;
	t_color	pixel_color;
	int		color_int;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			u = (double)x / (WIN_WIDTH - 1);
			v = (double)(WIN_HEIGHT - 1 - y) / (WIN_HEIGHT - 1);
			ray = camera_get_ray(&minirt->scene.camera, u, v);
			pixel_color = trace_ray(ray, &minirt->scene, MAX_DEPTH);
			color_int = color_to_int(pixel_color);
			put_pixel(&minirt->mlx_data, x, y, color_int);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt->mlx_data.mlx, minirt->mlx_data.win, 
		minirt->mlx_data.img, 0, 0);
}