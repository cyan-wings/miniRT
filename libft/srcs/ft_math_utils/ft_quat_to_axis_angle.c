/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_to_axis_angle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:14:30 by myeow             #+#    #+#             */
/*   Updated: 2024/08/12 15:55:50 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

void	ft_putendl_fd(char *s, int fd);

/*
 * Pre-normalisation of quarternions are done in this function.
 * Might remove pre-normalisation.
 */
double	ft_quat_to_axis_angle(t_quat *q, t_vec3 *out)
{
	double			r;
	double			s;
	const double	threshold = 1e-6;

	if (!q || !out)
	{
		ft_putendl_fd("Null pointer.", 2);
		return (0.0);
	}
	ft_quat_normalise(q);
	r = 2 * ft_acos(q->w);
	s = ft_sqrt(1 - q->w * q->w);
	if (s < threshold)
	{
		ft_putendl_fd("s below threshold.", 1);
		out->x = 0;
		out->y = 0;
		out->z = 0;
		return (r);
	}
	out->x = q->v.x / s;
	out->y = q->v.y / s;
	out->z = q->v.z / s;
	return (r);
}
