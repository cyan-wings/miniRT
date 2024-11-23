/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 00:38:29 by myeow             #+#    #+#             */
/*   Updated: 2024/08/07 21:56:10 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar_fd(char c, int fd);

static int	find_base(char *base)
{
	int	b;

	b = -1;
	while (base[++b])
	{
		if (b > 0)
		{
			if (base[b - 1] == base[b])
				return (-2);
		}
		if (base[b] == '+' || base[b] == '-')
			return (-3);
	}
	return (b);
}

void	ft_putnbr_base_fd(int nbr, char *base, int fd)
{
	int				b;
	unsigned int	u_nbr;

	b = -1;
	b = find_base(base);
	if (b < 2)
		return ;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		u_nbr = -1 * nbr;
	}
	else
		u_nbr = nbr;
	if (u_nbr >= (unsigned int) b)
		ft_putnbr_base_fd(u_nbr / b, base, fd);
	ft_putchar_fd(*(u_nbr % b + base), fd);
}
/*
int	main()
{
	char	*dec = "0123456789";
	char	*bin = "01";
	char	*hex = "0123456789ABCDEF";
	char	*oct = "poneyvif";

	return (0);
}
*/
