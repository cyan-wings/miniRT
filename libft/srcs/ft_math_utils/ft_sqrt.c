/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:23:50 by myeow             #+#    #+#             */
/*   Updated: 2024/08/21 17:21:18 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

void	ft_putendl_fd(char *s, int fd);

double	ft_sqrt_inverse_fast(double x)
{
	double			x2;
	double			y;
	const double	threehalfs = 1.5;
	t_conv			conv;

	if (x <= 0.0)
	{
		if (x < 0.0)
			ft_putendl_fd("Undefined.", 2);
		return (0.0);
	}
	x2 = x * 0.5;
	y = x;
	conv.d = y;
	conv.i = 0x5fe6eb50c7b537a9 - (conv.i >> 1);
	y = conv.d;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	return (y);
}

double	ft_sqrt_fast(double x)
{
	if (x <= 0.0)
	{
		if (x < 0.0)
			ft_putendl_fd("Undefined.", 2);
		return (0.0);
	}
	return (1.0 / ft_sqrt_inverse_fast(x));
}

double	ft_sqrt(double x)
{
	double	tolerance;
	double	guess;
	double	result;

	if (x < 0)
		ft_putendl_fd("Sqrt: Undefined.", 2);
	if (x == 0.0 || x == 1.0)
		return (x);
	tolerance = 1e-10;
	guess = x;
	result = 0.5 * (guess + 1);
	while (ft_abs(result - guess) >= tolerance)
	{
		guess = result;
		result = 0.5 * (guess + x / guess);
	}
	return (result);
}
