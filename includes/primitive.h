/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVE_H
# define PRIMITIVE_H

# include "ft_math_utils.h"
# include "hit.h"
# include "material.h"
# include "ray.h"

// Primitive types
typedef enum e_primitive_type
{
	ERROR,
	SPHERE,
	PLANE,
	CYLINDER
}	t_p_type;

// Sphere structure
typedef struct s_primitive_sphere
{
	t_vec3		center;
	double		radius;
}	t_p_sph;

// Plane structure
typedef struct s_primitive_plane
{
	t_vec3		point;
	t_vec3		normal;
}	t_p_pln;

// Cylinder structure
typedef struct s_primitive_cylinder
{
	t_vec3		center;
	t_vec3		axis;
	double		radius;
	double		height;
}	t_p_cyl;

typedef union u_primitive_data
{
	t_p_sph	sph;
	t_p_pln	pln;
	t_p_cyl	cyl;
}	t_p_data;

// Primitive structure
typedef struct s_primitive
{
	t_p_type	type;
	t_p_data	data;
	t_material	mat;
	t_hit		(*intersect_fn)(t_ray, void *, t_material *);
}	t_prm;

// Sphere intersection variables
typedef struct s_sphere_intersect
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	t;
}	t_sphere_intersect;

// Cylinder intersection variables
typedef struct s_cylinder_intersect
{
	t_vec3	axis_n;
	double	half_h;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	t_side;
	double	denom;
	t_vec3	top_cap_center;
	t_vec3	btm_cap_center;
	double	t_top_cap;
	double	t_btm_cap;
	t_hit	best_hit;
}	t_cylinder_intersect;

// Collision detection
t_hit		intersect_cylinder(t_ray ray, void *cylinder, t_material *mat);
t_hit		intersect_plane(t_ray ray, void *plane, t_material *mat);
t_hit		intersect_sphere(t_ray ray, void *sphere, t_material *mat);

#endif
