/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main_loop(t_minirt *minirt)
{
	int		rpp;

	if (!minirt->rendered)
	{
		if (minirt->current_y < WIN_HEIGHT)
		{
			rpp = minirt->scene.camera.rays_per_pixel;
			if (rpp < 1)
				rpp = 1;
			render_line(minirt, minirt->current_y, rpp);
			minirt->current_y++;
			if (minirt->current_y % 10 == 0 || minirt->current_y == WIN_HEIGHT)
				mlx_put_image_to_window(minirt->mlx_data.mlx,
					minirt->mlx_data.win, minirt->mlx_data.img, 0, 0);
		}
		else
		{
			minirt->rendered = 1;
			ft_printf("Rendering complete\n");
		}
	}
	return (0);
}

int	init_mlx(t_mlx_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!data->win)
		return (0);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		return (0);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		return (0);
	return (1);
}

int	handle_key(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_ESC)
	{
		cleanup_mlx(&minirt->mlx_data);
		exit(0);
	}
	return (0);
}

int	handle_close(t_minirt *minirt)
{
	cleanup_mlx(&minirt->mlx_data);
	exit(0);
}

void	cleanup_mlx(t_mlx_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
