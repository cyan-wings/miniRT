/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_mult.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:44:47 by myeow             #+#    #+#             */
/*   Updated: 2024/08/12 19:44:49 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

/*
 * Caution: ft_quat_mult(q1, q2) != ft_quat_mult(q2 * q1)
 *
 * May want to normalise the quarternions based on needs.
 */
void	ft_quat_mult(t_quat *q1, t_quat *q2, t_quat *out)
{
	if (!q1 || !q2 || !out)
		return ;
	out->w = q1->w * q2->w - q1->v.x * q2->v.x - q1->v.y * q2->v.y
		- q1->v.z * q2->v.z;
	out->v.x = q1->w * q2->v.x + q1->v.x * q2->w + q1->v.y * q2->v.z
		- q1->v.z * q2->v.y;
	out->v.y = q1->w * q2->v.y - q1->v.x * q2->v.z + q1->v.y * q2->w
		+ q1->v.z * q2->v.x;
	out->v.z = q1->w * q2->v.z + q1->v.x * q2->v.y - q1->v.y * q2->v.x
		+ q1->v.z * q2->w;
}
