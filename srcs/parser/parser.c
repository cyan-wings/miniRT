/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	int	(*parse_function(const char *str))
(char**, t_scene *)
{
	static int	(*func[])(char **, t_scene *) = {
		parse_ambient, parse_camera, parse_light,
		parse_sphere, parse_plane, parse_cylinder,
		NULL
	};
	const char	*obj_types[] = {
		"A", "C", "L",
		"sp", "pl", "cy",
		NULL
	};
	int			i;

	i = 0;
	while (obj_types[i] && ft_strcmp(str, obj_types[i]))
		++i;
	return (func[i]);
}

static int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		result;

	if (!line || line[0] == '#' || line[0] == '\n')
		return (1);
	tokens = ft_split_tok(line, " \t");
	if (!tokens || !tokens[0])
	{
		if (tokens)
			ft_memdel((void **)&tokens);
		return (1);
	}
	result = parse_function(tokens[0])(tokens, scene);
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
