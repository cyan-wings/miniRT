/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# define MAX_OBJECTS 100

# include "ft_math_utils.h"
# include "color.h"
# include "primitive.h"

/* Camera structure */
typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	up;
	t_vec3	right;
	double	fov;
	double	aspect_ratio;
	double	viewport_width;
	double	viewport_height;
	double	scatter_angle;
	int		rays_per_pixel;
}	t_camera;

/* Light structure */
typedef struct s_light
{
	t_vec3	position;
	t_color	color;
	double	brightness;
}	t_light;

/* Ambient light structure */
typedef struct s_ambient
{
	t_color	color;
	double	ratio;
}	t_ambient;

/* Scene structure */
typedef struct s_scene
{
	t_camera	camera;
	t_light		light;
	t_ambient	ambient;
	t_prm		objects[MAX_OBJECTS];
	int			object_count;
}	t_scene;

#endif
