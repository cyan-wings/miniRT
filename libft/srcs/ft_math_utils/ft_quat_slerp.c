/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_slerp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:33:30 by myeow             #+#    #+#             */
/*   Updated: 2024/08/22 17:26:54 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

static void	ft_quat_slerp_helper(t_quat *q1, t_quat *q2, t_quat *out)
{
	out->w = q1->w * 0.5 + q2->w * 0.5;
	out->v.x = q1->v.x * 0.5 + q2->v.x * 0.5;
	out->v.y = q1->v.y * 0.5 + q2->v.y * 0.5;
	out->v.z = q1->v.z * 0.5 + q2->v.z * 0.5;
}

static void	quat_theta_reverse(t_quat *q2, double *dot_product)
{
	q2->w = -q2->w;
	q2->v.x = -q2->v.x;
	q2->v.y = -q2->v.y;
	q2->v.z = -q2->v.z;
	*dot_product = -(*dot_product);
}

/*
 * theta := [dot product, half_theta, sin_half_theta]
 */
void	ft_quat_slerp(t_quat *q1, t_quat *q2, double t, t_quat *out)
{
	double	theta[3];
	double	ratio_a;
	double	ratio_b;

	ft_quat_normalise(q1);
	ft_quat_normalise(q2);
	theta[0] = (q1->w * q2->w) + (q1->v.x * q2->v.x)
		+ (q1->v.y * q2->v.y) + (q1->v.z * q2->v.z);
	if (theta[0] < 0.0)
		quat_theta_reverse(q2, &theta[0]);
	if (theta[0] >= 1.0)
		return (ft_quatcpy(q1, out));
	theta[1] = ft_acos(theta[0]);
	theta[2] = ft_sqrt(1.0 - theta[0] * theta[0]);
	if (ft_abs(theta[2]) >= QUAT_EPS)
	{
		ratio_a = ft_sin((1 - t) * theta[1]) / theta[2];
		ratio_b = ft_sin(t * theta[1]) / theta[2];
		out->w = q1->w * ratio_a + q2->w * ratio_b;
		out->v.x = q1->v.x * ratio_a + q2->v.x * ratio_b;
		out->v.y = q1->v.y * ratio_a + q2->v.y * ratio_b;
		out->v.z = q1->v.z * ratio_a + q2->v.z * ratio_b;
		return ;
	}
	ft_quat_slerp_helper(q1, q2, out);
}
