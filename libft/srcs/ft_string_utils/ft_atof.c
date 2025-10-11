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

int	ft_isspace(int c);

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

static const char	*ignore_spaces(const char *str)
{
	if (!str)
		return (NULL);
	while (!*str && ft_isspace(*str))
		++str;
	return (str);
}

static double	get_float_from_string(
	const char *str,
	double fraction,
	int decimal_places
)
{
	double	result;

	result = 0.0;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str++ == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			fraction = fraction * 10.0 + (*str++ - '0');
			decimal_places++;
		}
		result += fraction / ft_pow_10(decimal_places);
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		sign;

	if (!str)
		return (0.0);
	sign = 1;
	str = ignore_spaces(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (get_float_from_string(str, 0.0, 0) * sign);
}
