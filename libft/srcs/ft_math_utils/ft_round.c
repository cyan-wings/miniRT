/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:56:14 by myeow             #+#    #+#             */
/*   Updated: 2024/08/10 16:13:18 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_floor(double d);

double	ft_ceil(double d);

double	ft_round(double d)
{
	double	floor_val;
	double	ceil_val;
	double	diff_from_floor;

	if (d != d)
		return (d);
	if (d == 0.0)
		return (0.0);
	floor_val = ft_floor(d);
	ceil_val = ft_ceil(d);
	diff_from_floor = d - floor_val;
	if (diff_from_floor < 0.5)
		return (floor_val);
	else if (diff_from_floor > 0.5)
		return (ceil_val);
	else
	{
		if (d < 0)
			return (floor_val);
		else
			return (ceil_val);
	}
}
