/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	ft_vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	ft_vec3_length(t_vec3 v)
{
	return (ft_sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	ft_vec3_normalize(t_vec3 v)
{
	double	length;

	length = ft_vec3_length(v);
	if (length < EPSILON)
		return (v);
	return (ft_vec3_div(v, length));
}

t_vec3	ft_vec3_reflect(t_vec3 v, t_vec3 n)
{
	return (ft_vec3_sub(v, ft_vec3_mult(n, 2.0 * ft_vec3_dot(v, n))));
}
