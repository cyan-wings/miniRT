/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"

// Material types
typedef enum e_material_type
{
	DIFFUSE,
	GLASS
}	t_m_type;

typedef struct s_material_diffuse
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_m_dif;

typedef struct s_material_glass
{
	double	transparency;
	double	refractive_index;
	double	fuzz;
}	t_m_gls;

typedef union u_material_data
{
	t_m_dif	dif;
	t_m_gls	gls;
}	t_mat_data;

// Material structure
typedef struct s_material
{
	t_m_type		type;
	t_color			color;
	t_mat_data		data;
}	t_material;

#endif
