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

static int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		result;

	if (!line || line[0] == '#' || line[0] == '\n')
		return (1);
	tokens = ft_split_whitespace(line);
	if (!tokens || !tokens[0])
	{
		if (tokens)
			ft_free_array((void **)tokens);
		return (1);
	}
	result = 1;
	if (ft_strcmp(tokens[0], "A") == 0)
		result = parse_ambient(tokens, &scene->ambient);
	else if (ft_strcmp(tokens[0], "C") == 0)
		result = parse_camera(tokens, &scene->camera);
	else if (ft_strcmp(tokens[0], "L") == 0)
		result = parse_light(tokens, &scene->light);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		result = parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		result = parse_plane(tokens, scene);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		result = parse_cylinder(tokens, scene);
	ft_free_array((void **)tokens);
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
			break;
		result = parse_line(line, scene);
		free(line);
	}
	close(fd);
	return (result);
}
