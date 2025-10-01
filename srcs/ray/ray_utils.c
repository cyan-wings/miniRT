/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = ft_vec3_normalize(direction);
	return (ray);
}

t_vec3	ray_at(t_ray ray, double t)
{
	return (ft_vec3_add(ray.origin, ft_vec3_mult(ray.direction, t)));
}