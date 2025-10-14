/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	return (result);
}

t_color	color_mult(t_color c, double t)
{
	t_color	result;

	result.r = c.r * t;
	result.g = c.g * t;
	result.b = c.b * t;
	return (result);
}

t_color	color_multiply(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r * b.r;
	result.g = a.g * b.g;
	result.b = a.b * b.b;
	return (result);
}

t_color	color_clamp(t_color a, double low, double high)
{
	t_color	result;

	result.r = clamp(a.r, low, high);
	result.g = clamp(a.g, low, high);
	result.b = clamp(a.b, low, high);
	return (result);
}

int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(clamp(c.r, 0.0, 1.0) * 255);
	g = (int)(clamp(c.g, 0.0, 1.0) * 255);
	b = (int)(clamp(c.b, 0.0, 1.0) * 255);
	return ((r << 16) | (g << 8) | b);
}
