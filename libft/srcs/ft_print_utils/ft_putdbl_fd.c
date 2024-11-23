/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdbl_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:00:01 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 21:45:41 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_modf(double d, double *i);

void	ft_putnbr_fd(int n, int fd);

void	ft_putchar_fd(char c, int fd);

void	ft_putdbl_fd(double d, int fd)
{
	double	int_part;
	double	fractional_part;

	if (d < 0)
	{
		ft_putchar_fd('-', fd);
		d = -d;
	}
	fractional_part = ft_modf(d, &int_part);
	ft_putnbr_fd(int_part, fd);
	ft_putchar_fd('.', fd);
	fractional_part *= 10000;
	if (fractional_part < 0)
		fractional_part = -fractional_part;
	ft_putnbr_fd((int)fractional_part, fd);
}
