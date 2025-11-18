/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	has_valid_extension(const char *filename, const char *ext)
{
	int	filename_len;
	int	ext_len;

	if (!filename || !ext)
		return (0);
	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (filename_len < ext_len)
		return (0);
	return (ft_strcmp(filename + filename_len - ext_len, ext) == 0);
}

static int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd(ERR_USAGE, 2);
		return (0);
	}
	if (!has_valid_extension(argv[1], ".rt"))
	{
		ft_putendl_fd("Error: File must have .rt extension", 2);
		return (0);
	}
	return (1);
}

static void	init_minirt(t_minirt *minirt)
{
	ft_memset(minirt, 0, sizeof(t_minirt));
}

int	parse_scene(const char *filename, t_scene *scene);

int	main(int argc, char **argv)
{
	t_minirt	minirt;

	if (!validate_arguments(argc, argv))
		return (1);
	init_minirt(&minirt);
	if (!parse_scene(argv[1], &minirt.scene))
		error_exit(ERR_PARSE);
	if (!init_mlx(&minirt.mlx_data))
		cleanup_and_exit(&minirt, ERR_MLX);
	camera_init(&minirt.scene.camera);
	mlx_loop_hook(minirt.mlx_data.mlx, main_loop, &minirt);
	mlx_hook(minirt.mlx_data.win, ON_KEYDOWN, KEY_PRESS_MASK,
		handle_key, &minirt);
	mlx_hook(minirt.mlx_data.win, ON_DESTROY, NO_EVENT_MASK,
		handle_close, &minirt);
	mlx_loop(minirt.mlx_data.mlx);
	return (0);
}
