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

t_ray	calc_reflected_ray(t_hit *hit, t_vec3 reflected_dir);

static t_color	trace_glass(t_ray ray, t_hit hit, t_scene *scene, int depth)
{
	t_color	attenuation;
	double	ri;
	t_vec3	unit_direction;
	double	cos_theta;
	double	sin_theta;
	t_vec3	direction;

	attenuation = hit.material.color;
	ri = hit.front_face ? (1.0 / hit.material.refractive_index)
		: hit.material.refractive_index;
	unit_direction = ft_vec3_normalize(ray.direction);
	cos_theta = fmin(ft_vec3_dot(ft_vec3_mult(unit_direction, -1.0),
				hit.normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	
	// Check total internal reflection first (must reflect)
	// Then use Schlick for probabilistic reflection/refraction mix
	if (ri * sin_theta > 1.0
		|| schlick_reflectance(cos_theta, ri) > random_double())
	{
		// Reflect: either TIR or Fresnel says reflect
		if (!hit.front_face)
			attenuation = (t_color){1, 1, 1};
		direction = ft_vec3_reflect(unit_direction, hit.normal);
	}
	else
	{
		// Refract: Fresnel says refract
		direction = ft_vec3_refract(unit_direction, hit.normal, ri);
		if (ft_vec3_length(direction) < EPSILON)
			direction = ft_vec3_reflect(unit_direction, hit.normal);
	}
	
	if (hit.material.fuzz > EPSILON)
		direction = ft_vec3_add(direction,
				ft_vec3_mult(ft_vec3_random_unit_vector(), hit.material.fuzz));
	direction = ft_vec3_normalize(direction);
	return (color_multiply(trace_ray(calc_refracted_ray(&hit, direction),
				scene, depth - 1), attenuation));
}

//	return (color_add(
//		local_color,
//		color_multiply(color_clamp(reflected_color, 0, 1),
//		hit.material.color)));
//	return (color_add(
//		color_scale(local_color, (1.0 - hit.material.shininess)),
//		color_scale(reflected_color, hit.material.shininess)));
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
	if (hit.material.transparency > EPSILON)
		return (trace_glass(ray, hit, scene, depth));
	local_color = calculate_lighting(hit, scene, ray);
	reflected_dir = ft_vec3_reflect(ray.direction, hit.normal);
	if (ft_vec3_length(reflected_dir) < EPSILON)
		return (local_color);
	reflected_color = trace_ray(calc_reflected_ray(&hit, reflected_dir),
			scene, depth - 1);
	return (color_add(
			local_color,
			color_scale(color_multiply(reflected_color, hit.material.color),
				0.5)));
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
		pixel_color = color_add(pixel_color, trace_ray(ray, scene, MAX_DEPTH));
	}
	return (color_scale(pixel_color, 1 / (double)rpp));
}

void	render_scene(t_minirt *minirt)
{
	int		x;
	int		y;
	int		rpp;
	int		color_int;

	y = 0;
	rpp = minirt->scene.camera.rays_per_pixel;
	if (rpp < 1)
		rpp = 1;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color_int = color_to_int(get_pixel_color(rpp, x, y,
						&minirt->scene));
			put_pixel(&minirt->mlx_data, x, y, color_int);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt->mlx_data.mlx, minirt->mlx_data.win,
		minirt->mlx_data.img, 0, 0);
}
