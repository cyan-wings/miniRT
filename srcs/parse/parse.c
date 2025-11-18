/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include "parse.h"
#include "get_next_line.h"

int		parse_ambient(char **tokens, t_scene *scene);
int		parse_camera(char **tokens, t_scene *scene);
int		parse_light(char **tokens, t_scene *scene);

t_prm	parse_cylinder(char **tokens);
t_prm	parse_plane(char **tokens);
t_prm	parse_sphere(char **tokens);
t_prm	parse_error_prm(char **tokens);

t_parse_meta_fn	get_meta_fn(const char *id)
{
	static const t_meta_ft	table[] = {
	{"A", parse_ambient}, {"C", parse_camera}, {"L", parse_light},
	{NULL, NULL}
	};
	int						i;

	i = 0;
	while (table[i].id && ft_strcmp(id, table[i].id))
		++i;
	return (table[i].fn);
}

t_parse_prm_fn	get_prm_fn(const char *id)
{
	static const t_prm_ft	table[] = {
	{"sp", parse_sphere}, {"pl", parse_plane}, {"cy", parse_cylinder},
	{NULL, parse_error_prm}
	};
	int						i;

	i = 0;
	while (table[i].id && ft_strcmp(id, table[i].id))
		++i;
	return (table[i].fn);
}

static int	parse_function(t_scene *scene, char **tokens)
{
	t_parse_meta_fn	meta_fn;
	t_parse_prm_fn	prm_fn;
	int				result;

	result = 0;
	meta_fn = get_meta_fn(tokens[0]);
	if (meta_fn)
	{
		result = meta_fn(tokens, scene);
		return (result);
	}
	prm_fn = get_prm_fn(tokens[0]);
	if (prm_fn)
	{
		scene->objects[scene->object_count] = prm_fn(tokens);
		if (scene->objects[scene->object_count].type == ERROR)
			return (0);
		scene->object_count++;
		result = 1;
	}
	return (result);
}

// Handle max objects error?
static int	parse_line(char *line, t_scene *scene)
{
	char			**tokens;
	int				result;

	if (line[0] == 0 || line[0] == '#' || line[0] == '\n')
		return (1);
	tokens = ft_split_tok(line, " \t");
	if (!tokens || !tokens[0])
	{
		if (tokens)
			ft_memdel((void **)&tokens);
		return (1);
	}
	result = parse_function(scene, tokens);
	ft_memdel((void **)&tokens);
	return (result);
}

int	parse_scene(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
	int		result;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	ft_memset(scene, 0, sizeof(t_scene));
	apply_scene_defaults(scene);
	result = 1;
	while (result)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		result = parse_line(line, scene);
		ft_memdel((void **)&line);
	}
	close(fd);
	return (result);
}
