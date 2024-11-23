/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_fractional.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:04:43 by myeow             #+#    #+#             */
/*   Updated: 2024/07/30 23:05:47 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_fractional(double d);

double	ft_rev_fractional(double d)
{
	return (1 - ft_fractional(d));
}
