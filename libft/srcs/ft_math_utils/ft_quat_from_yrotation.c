/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_from_yrotation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:30:44 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 18:31:08 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

void	ft_quat_from_yrotation(double r, t_quat *out)
{
	t_vec3	v;

	if (!out)
		return ;
	v = (t_vec3){0, 1.0, 0};
	ft_quat_from_axis_angle(&v, r, out);
}
