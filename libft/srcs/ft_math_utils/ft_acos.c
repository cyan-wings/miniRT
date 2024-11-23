/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:47:32 by myeow             #+#    #+#             */
/*   Updated: 2024/08/11 01:50:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

void	ft_putendl_fd(char *s, int fd);

double	ft_asin(double x);

double	ft_acos(double x)
{
	if (x < -1.0 || x > 1.0)
	{
		ft_putendl_fd("Undefined.", 2);
		return (0);
	}
	return (PI / 2 - ft_asin(x));
}
