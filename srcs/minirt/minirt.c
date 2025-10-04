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

static int	validate_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd(ERR_USAGE, 2);
		return (0);
	}
	if (!is_valid_extension(argv[1], ".rt"))
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

int	main(int argc, char **argv)
{
	t_minirt	minirt;

	if (!validate_args(argc, argv))
		return (1);
	init_minirt(&minirt);
	if (!parse_scene(argv[1], &minirt.scene))
		error_exit(ERR_PARSE);
	if (!init_mlx(&minirt.mlx_data))
		cleanup_and_exit(&minirt, ERR_MLX);
	camera_init(&minirt.scene.camera);
	render_scene(&minirt);
	mlx_key_hook(minirt.mlx_data.win, handle_key, &minirt);
	mlx_hook(minirt.mlx_data.win, 17, 0, handle_close, &minirt);
	mlx_loop(minirt.mlx_data.mlx);
	return (0);
}
