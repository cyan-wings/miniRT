/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_from_axis_angle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:15:19 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 21:46:23 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

void	ft_putendl_fd(char *s, int fd);

static double	calc_magnitude(t_vec3 *v)
{
	return (ft_sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

void	ft_quat_from_axis_angle(t_vec3 *axis, double r, t_quat *out)
{
	double	c;
	double	m;

	if (!out || !axis)
		return ;
	m = calc_magnitude(axis);
	if (m == 0.0)
	{
		ft_putendl_fd("Vector magnitude is 0.", 2);
		return ;
	}
	c = ft_sin(r / 2.0);
	out->w = ft_cos(r / 2.0);
	out->v.x = c * (axis->x / m);
	out->v.y = c * (axis->y / m);
	out->v.z = c * (axis->z / m);
}
