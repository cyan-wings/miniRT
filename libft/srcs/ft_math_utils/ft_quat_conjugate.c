/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_conjugate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:00:30 by myeow             #+#    #+#             */
/*   Updated: 2024/08/12 16:02:16 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

void	ft_quat_conjugate(t_quat *q, t_quat *out)
{
	if (!out)
		return ;
	out->w = q->w;
	out->v.x = -q->v.x;
	out->v.y = -q->v.y;
	out->v.z = -q->v.z;
}
