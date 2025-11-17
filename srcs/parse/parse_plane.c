/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_prm	parse_plane(char **tokens)
{
	t_prm	pln;

	pln = (t_prm){0};
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (pln);
	pln.type = PLANE;
	pln.data.pln.point = parse_vector(tokens[1]);
	pln.data.pln.normal = ft_vec3_normalize(parse_vector(tokens[2]));
	parse_material(&tokens[3], &pln.mat);
	pln.intersect_fn = intersect_plane;
	return (pln);
}
