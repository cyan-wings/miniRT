/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_normalise.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:55:04 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 20:40:59 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

void	ft_putendl_fd(char *s, int fd);

void	ft_quat_normalise(t_quat *out)
{
	double			m;
	const double	threshold = 1e-6;

	if (!out)
		return ;
	m = ft_quatget_magnitude(out);
	if (m < threshold)
	{
		ft_putendl_fd("Quarternion magnitude too small to normalise.", 2);
		return ;
	}
	out->w /= m;
	out->v.x /= m;
	out->v.y /= m;
	out->v.z /= m;
}
