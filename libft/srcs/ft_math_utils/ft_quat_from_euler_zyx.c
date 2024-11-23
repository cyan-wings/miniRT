/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_from_euler_zyx.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:11:27 by myeow             #+#    #+#             */
/*   Updated: 2024/08/12 15:16:47 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

/*
 * Half cos of roll: cs[0]
 * Half sin of roll: cs[1]
 * Half cos of pitch: cs[2]
 * Half sin of pitch: cs[3]
 * Half cos of yaw: cs[4]
 * Half sin of yaw: cs[5]
 *
 * Order is ZYX which means yaw is rotated first, then pitch, then roll.
 * No normalisation is needed.
 * Careful of gimbal lock.
 */
void	ft_quat_from_euler_zyx(t_vec3 *v, t_quat *out)
{
	const double	cs[6] = {
		ft_cos(v->x * 0.5),
		ft_sin(v->x * 0.5),
		ft_cos(v->y * 0.5),
		ft_sin(v->y * 0.5),
		ft_cos(v->z * 0.5),
		ft_sin(v->z * 0.5)
	};

	if (!v || !out)
		return ;
	out->w = cs[0] * cs[2] * cs[4] + cs[1] * cs[3] * cs[5];
	out->v.x = cs[1] * cs[2] * cs[4] - cs[0] * cs[3] * cs[5];
	out->v.y = cs[0] * cs[3] * cs[4] + cs[1] * cs[2] * cs[5];
	out->v.z = cs[0] * cs[2] * cs[5] - cs[1] * cs[3] * cs[4];
}
