/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:38:52 by myeow             #+#    #+#             */
/*   Updated: 2024/08/21 20:26:53 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math_utils.h"

/*
 * @vars
 * 	sq: squares
 * 	sc: scalars
 * 	p: pairs
 * 	tmp_x, tmp_y: Variables for safe copying when v and out are the same ptr.
 *
 * 	This function rotates the vector v by the quaternion q.
 * 	Quaternion q can be converted to axis-angle to comprehend or test.
 * 	Out is the resulting vector from the rotation.
 */
void	ft_quat_rotate(t_vec3 *v, t_quat *q, t_vec3 *out)
{
	const double	sq[4] = {
		q->w * q->w, q->v.x * q->v.x, q->v.y * q->v.y, q->v.z * q->v.z};
	const double	sc[3] = {
		q->w * q->v.x, q->w * q->v.y, q->w * q->v.z};
	const double	p[3] = {
		q->v.x * q->v.y, q->v.x * q->v.z, q->v.y * q->v.z};
	double			tmp_x;
	double			tmp_y;

	if (!q || !v || !out)
		return ;
	tmp_x = (sq[0] + sq[1] - sq[2] - sq[3]) * v->x
		+ 2 * (p[0] - sc[2]) * v->y
		+ 2 * (p[1] + sc[1]) * v->z;
	tmp_y = (sq[0] - sq[1] + sq[2] - sq[3]) * v->y
		+ 2 * (p[0] + sc[2]) * v->x
		+ 2 * (p[2] - sc[0]) * v->z;
	out->z = (sq[0] - sq[1] - sq[2] + sq[3]) * v->z
		+ 2 * (p[1] - sc[1]) * v->x
		+ 2 * (p[2] + sc[0]) * v->y;
	out->x = tmp_x;
	out->y = tmp_y;
}
