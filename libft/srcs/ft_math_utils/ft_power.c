/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:31:01 by myeow             #+#    #+#             */
/*   Updated: 2024/08/21 17:49:43 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_abs(double d);

double	ft_power(double x, int p)
{
	double			result;
	unsigned int	p_abs;

	if (x == 0 && p < 0)
		return (0);
	result = 1.0;
	p_abs = ft_abs(p);
	while (p_abs)
	{
		if (p_abs % 2 == 1)
			result *= x;
		x *= x;
		p_abs /= 2;
	}
	if (p < 0)
		result = 1.0 / result;
	return (result);
}
