/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	intersect_scene(t_ray ray, t_scene *scene)
{
	t_hit		best_hit;
	t_hit		curr_hit;
	double		closest_t;
	int			i;
	t_prm		prm;

	ft_memset(&best_hit, 0, sizeof(t_hit));
	closest_t = INFINITY_F;
	i = -1;
	while (++i < scene->object_count)
	{
		prm = scene->objects[i];
		curr_hit = prm.intersect_fn(ray, &prm.data, &prm.mat);
		if (curr_hit.hit && curr_hit.t < closest_t)
		{
			best_hit = curr_hit;
			closest_t = curr_hit.t;
		}
	}
	return (best_hit);
}
