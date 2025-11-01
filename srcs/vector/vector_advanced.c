/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/11/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ft_vec3_refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double	cos_theta;
	double	sin_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fmin(ft_vec3_dot(ft_vec3_mult(uv, -1.0), n), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (etai_over_etat * sin_theta > 1.0)
		return ((t_vec3){0, 0, 0});
	r_out_perp = ft_vec3_mult(
			ft_vec3_add(uv, ft_vec3_mult(n, cos_theta)),
			etai_over_etat);
	r_out_parallel = ft_vec3_mult(n,
			-sqrt(fabs(1.0 - ft_vec3_dot(r_out_perp, r_out_perp))));
	return (ft_vec3_add(r_out_perp, r_out_parallel));
}

t_vec3	ft_vec3_random_unit_vector(void)
{
	double	theta;
	double	phi;
	double	x;
	double	y;
	double	z;

	theta = 2.0 * M_PI * random_double();
	phi = acos(2.0 * random_double() - 1.0);
	x = sin(phi) * cos(theta);
	y = sin(phi) * sin(theta);
	z = cos(phi);
	return ((t_vec3){x, y, z});
}
