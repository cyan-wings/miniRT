/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quatget_magnitude.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:57:40 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 20:40:20 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

void	ft_putendl_fd(char *s, int fd);

double	ft_quatget_magnitude(t_quat *q)
{
	if (!q)
	{
		ft_putendl_fd("Null pointer.", 2);
		return (0.0);
	}
	return (ft_sqrt(q->w * q->w + q->v.x * q->v.x
			+ q->v.y * q->v.y + q->v.z * q->v.z));
}
