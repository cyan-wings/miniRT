/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	int_to_color(int color)
{
	t_color	result;

	result.r = ((color >> 16) & 0xFF) / 255.0;
	result.g = ((color >> 8) & 0xFF) / 255.0;
	result.b = (color & 0xFF) / 255.0;
	return (result);
}