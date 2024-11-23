/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:48:44 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 01:50:07 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putendl_fd(char *s, int fd);

double	ft_abs(double d);

double	ft_sin(double r);

double	ft_cos(double r);

double	ft_asin(double x)
{
	double			y;
	int				i;
	double			y_prime;
	const double	tolerance = 1e-10;

	if (x < -1.0 || x > 1.0)
	{
		ft_putendl_fd("Undefined.", 2);
		return (0);
	}
	y = x;
	i = -1;
	while (++i < 100)
	{
		y_prime = y - ((ft_sin(y) - x) / ft_cos(y));
		if (ft_abs(y_prime - y) < tolerance)
			return (y_prime);
		y = y_prime;
	}
	return (y);
}
