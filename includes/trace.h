/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "color.h"
# include "ft_math_utils.h"
# include "ray.h"
# include "hit.h"
# include "scene.h"

// Ray trace glass variables
typedef struct s_trace_glass
{
	t_color	attenuation;
	double	ri;
	t_vec3	unit_direction;
	double	cos_theta;
	double	sin_theta;
	t_vec3	direction;
}	t_trc_gls;

typedef struct s_glass_ray
{
	t_vec3	dir;
	t_color	color;
}	t_glass_ray;

t_color	trace_glass(t_ray ray, t_hit hit, t_scene *scene, int depth);

#endif
