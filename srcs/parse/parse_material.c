/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "parse.h"

// refactor and fix this pls
static void	parse_material_glass(char **tokens, t_material *mat)
{
	mat->type = GLASS;
	mat->data.gls.refractive_index = 1.5;
	mat->data.gls.fuzz = 0.0;
	mat->data.gls.transparency = 1.0;
	if (tokens[2])
		mat->data.gls.refractive_index = ft_atof(tokens[2]);
	else
		return ;
	if (tokens[3])
		mat->data.gls.fuzz = ft_atof(tokens[3]);
	else
		return ;
	if (tokens[4])
		mat->data.gls.transparency = ft_atof(tokens[4]);
	else
		return ;
}

// May want to change the formatting in the scene file
static void	parse_material_diffuse(char **tokens, t_material *mat)
{
	mat->type = DIFFUSE;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4])
		return ;
	mat->data.dif.ambient = ft_atof(tokens[1]);
	mat->data.dif.diffuse = ft_atof(tokens[2]);
	mat->data.dif.specular = ft_atof(tokens[3]);
	mat->data.dif.shininess = ft_atof(tokens[4]);
}

void	parse_material(char **tokens, t_material *mat)
{
	mat->color = parse_color(tokens[0]);
	if (tokens[1] && ft_strcmp(tokens[1], "glass") == 0)
		parse_material_glass(tokens, mat);
	else
		parse_material_diffuse(tokens, mat);
}
