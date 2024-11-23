/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:47:29 by myeow             #+#    #+#             */
/*   Updated: 2024/08/10 13:58:18 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_modf(double d, double *i)
{
	double	frac_part;

	*i = (double)((long long)d);
	frac_part = d - *i;
	if (d < 0 && frac_part != 0.0)
	{
		*i -= 1;
		frac_part = d - *i;
	}
	return (frac_part);
}
