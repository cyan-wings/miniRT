/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_prm	parse_sphere(char **tokens)
{
	t_prm	sph;

	sph = (t_prm){0};
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (sph);
	sph.type = SPHERE;
	sph.data.sph.center = parse_vector(tokens[1]);
	sph.data.sph.radius = ft_atof(tokens[2]) / 2.0;
	if (!parse_material(&tokens[3], &sph.mat))
		return ((t_prm){0});
	sph.intersect_fn = intersect_sphere;
	return (sph);
}
