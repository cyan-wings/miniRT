/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"

static double	ft_pow_10(int exp)
{
	double	result;

	result = 1.0;
	while (exp > 0)
	{
		result *= 10.0;
		exp--;
	}
	while (exp < 0)
	{
		result /= 10.0;
		exp++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		decimal_places;

	if (!str)
		return (0.0);
	result = 0.0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		fraction = 0.0;
		decimal_places = 0;
		while (*str >= '0' && *str <= '9')
		{
			fraction = fraction * 10.0 + (*str - '0');
			decimal_places++;
			str++;
		}
		result += fraction / ft_pow_10(decimal_places);
	}
	return (result * sign);
}