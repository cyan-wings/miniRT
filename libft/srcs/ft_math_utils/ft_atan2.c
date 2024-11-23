/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atan2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 00:45:45 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 01:51:16 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

double	ft_atan(double x);

void	ft_putendl_fd(char *s, int fd);

double	ft_atan2(double y, double x)
{
	if (x > 0)
		return (ft_atan(y / x));
	if (x < 0 && y >= 0)
		return (ft_atan(y / x) + PI);
	if (x < 0 && y < 0)
		return (ft_atan(y / x) - PI);
	if (x == 0.0)
	{
		if (y > 0)
			return (PI / 2);
		else if (y < 0)
			return (-PI / 2);
	}
	ft_putendl_fd("Undefined.", 2);
	return (0.0);
}
