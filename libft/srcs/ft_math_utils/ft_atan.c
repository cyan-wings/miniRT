/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:51:46 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 01:50:56 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

double	ft_sqrt(double x);

double	ft_asin(double x);

double	ft_atan(double x)
{
	double	denom;
	double	argument;

	if (x < -1.0 || x > 1.0)
	{
		if (x > 0)
			return (PI / 2 - ft_atan(1 / x));
		else
			return (-PI / 2 - ft_atan(1 / x));
	}
	denom = ft_sqrt(1 + x * x);
	argument = x / denom;
	return (ft_asin(argument));
}
