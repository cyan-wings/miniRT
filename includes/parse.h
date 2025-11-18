/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "ft_string_utils.h"
# include "ft_mem_utils.h"
# include "primitive.h"
# include "scene.h"

typedef int		(*t_parse_meta_fn)(char **, t_scene *);
typedef t_prm	(*t_parse_prm_fn)(char **);

typedef struct s_meta_function_table
{
	const char		*id;
	t_parse_meta_fn	fn;
}	t_meta_ft;

typedef struct s_prm_function_table
{
	const char		*id;
	t_parse_prm_fn	fn;
}	t_prm_ft;

t_color	parse_color(char *str);
void	parse_material(char **tokens, t_material *mat);
t_vec3	parse_vector(char *str);

void	apply_scene_defaults(t_scene *scene);
double	ft_deg_to_rad(double deg);

#endif
