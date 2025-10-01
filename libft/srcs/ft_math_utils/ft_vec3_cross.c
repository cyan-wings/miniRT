/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_cross.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

t_vec3	ft_vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}