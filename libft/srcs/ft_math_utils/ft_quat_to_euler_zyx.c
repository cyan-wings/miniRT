/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_to_euler_zyx.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:12:59 by myeow             #+#    #+#             */
/*   Updated: 2024/08/12 15:59:31 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

/*
 * Pre-normalisation of quarternions are done in this function.
 */
void	ft_quat_to_euler_zyx(t_quat *q, t_vec3 *out)
{
	double	sinr_cosp;
	double	cosr_cosp;
	double	sinp;
	double	siny_cosp;
	double	cosy_cosp;

	if (!q || !out)
		return ;
	ft_quat_normalise(q);
	sinr_cosp = 2.0 * (q->w * q->v.x + q->v.y * q->v.z);
	cosr_cosp = 1.0 - 2.0 * (q->v.x * q->v.x + q->v.y * q->v.y);
	out->x = ft_atan2(sinr_cosp, cosr_cosp);
	sinp = 2.0 * (q->w * q->v.y - q->v.z * q->v.x);
	if (ft_abs(sinp) >= 1)
		out->y = ft_copysign(PI_2, sinp);
	else
		out->y = ft_asin(sinp);
	siny_cosp = 2.0 * (q->w * q->v.z + q->v.x * q->v.y);
	cosy_cosp = 1.0 - 2.0 * (q->v.y * q->v.y + q->v.z * q->v.z);
	out->z = ft_atan2(siny_cosp, cosy_cosp);
}
