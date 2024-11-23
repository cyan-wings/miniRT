/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_isequal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:07:46 by myeow             #+#    #+#             */
/*   Updated: 2024/08/09 22:14:06 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

int	ft_quat_isequal(t_quat *q1, t_quat *q2)
{
	if (ft_abs(q1->w - q2->w) <= QUAT_EPS)
		return (0);
	if (ft_abs(q1->v.x - q2->v.x) <= QUAT_EPS)
		return (0);
	if (ft_abs(q1->v.y - q2->v.y) <= QUAT_EPS)
		return (0);
	if (ft_abs(q1->v.z - q2->v.z) <= QUAT_EPS)
		return (0);
	return (1);
}
