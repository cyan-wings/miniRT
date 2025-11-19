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

int			main_loop(t_minirt *minirt)
{
	if (minirt->rendered)
		return (0);
	if (minirt->current_y >= WIN_HEIGHT)
	{
		minirt->rendered = 1;
		return (0);
	}
	render_line(minirt, minirt->current_y, minirt->scene.camera.rays_per_pixel);
	mlx_put_image_to_window(minirt->mlx_data.mlx, minirt->mlx_data.win,
		minirt->mlx_data.img, 0, 0);
	minirt->current_y++;
	return (0);
}