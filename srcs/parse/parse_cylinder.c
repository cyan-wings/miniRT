/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_prm	parse_cylinder(char **tokens)
{
	t_prm	cyl;

	cyl = (t_prm){0};
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		return (cyl);
	cyl.type = CYLINDER;
	cyl.data.cyl.center = parse_vector(tokens[1]);
	cyl.data.cyl.axis = ft_vec3_normalize(parse_vector(tokens[2]));
	cyl.data.cyl.radius = ft_atof(tokens[3]) / 2.0;
	cyl.data.cyl.height = ft_atof(tokens[4]);
	if (!parse_material(&tokens[5], &cyl.mat))
		return ((t_prm){0});
	cyl.intersect_fn = intersect_cylinder;
	return (cyl);
}
