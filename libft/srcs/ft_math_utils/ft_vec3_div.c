/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_div.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

t_vec3	ft_vec3_div(t_vec3 v, double t)
{
	t_vec3	result;

	if (ft_abs(t) < 1e-6)
		return (v);
	result.x = v.x / t;
	result.y = v.y / t;
	result.z = v.z / t;
	return (result);
}