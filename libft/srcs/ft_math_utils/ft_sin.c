/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:44:16 by myeow             #+#    #+#             */
/*   Updated: 2024/08/10 22:54:18 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

double	ft_abs(double d);

double	ft_sin(double r)
{
	double			term;
	double			result;
	int				i;
	const double	tolerance = 1e-10;

	while (r > PI)
		r -= 2 * PI;
	while (r < -PI)
		r += 2 * PI;
	term = r;
	result = r;
	i = 1;
	while (ft_abs(term) > tolerance)
	{
		term *= -r * r / ((2 * i) * (2 * i + 1));
		result += term;
		++i;
	}
	return (result);
}
