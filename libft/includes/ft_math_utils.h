/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:38 by myeow             #+#    #+#             */
/*   Updated: 2024/08/12 19:42:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_UTILS_H
# define FT_MATH_UTILS_H

# include <stdint.h>

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# ifndef PI_2
#  define PI_2 1.57079632679489661923
# endif

# ifndef PI_4
#  define PI_4 0.78539816339744830962
# endif

# ifndef ATAN_TABLE_ITERS
#  define ATAN_TABLE_ITERS 16
# endif

# ifndef K_FACTOR
#  define K_FACTOR 0.6072529350088812561694
# endif

# ifndef QUAT_EPS
#  define QUAT_EPS 1e-4
# endif

typedef struct s_2d_vector
{
	double	x;
	double	y;
}			t_vec2;

typedef struct s_3d_vector
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_quaternion
{
	double	w;
	t_vec3	v;
}			t_quat;

typedef union s_conv
{
	double		d;
	uint64_t	i;
}				t_conv;

double				ft_abs(double d);
double				ft_copysign(double x, double y);
void				ft_swap(double *a, double *b);
double				ft_modf(double d, double *i);
double				ft_floor(double d);
double				ft_ceil(double d);
double				ft_round(double d);
double				ft_fractional(double d);
double				ft_rev_fractional(double d);
double				ft_fmod(double x, double y);
double				ft_sqrt_inverse_fast(double x);
double				ft_sqrt_fast(double x);
double				ft_sqrt(double x);
unsigned long long	ft_factorial(int x);
double				ft_power(double x, int p);
double				ft_atan_table(int i);
double				ft_sin(double r);
double				ft_cos(double r);
double				ft_tan(double r);
double				ft_asin(double x);
double				ft_acos(double x);
double				ft_atan(double x);
double				ft_atan2(double y, double x);

//QUATERNION_UTILS
void				ft_quatset(double w, t_vec3 v, t_quat *out);
void				ft_quatset_id(t_quat *out);
void				ft_quatcpy(t_quat *q, t_quat *out);
int					ft_quat_isequal(t_quat *q1, t_quat *q2);
void				ft_quat_print(t_quat *q);
void				ft_quat_from_axis_angle(t_vec3 *axis, double r, \
		t_quat *out);
void				ft_quat_from_xrotation(double r, t_quat *out);
void				ft_quat_from_yrotation(double r, t_quat *out);
void				ft_quat_from_zrotation(double r, t_quat *out);
double				ft_quatget_magnitude(t_quat *q);
void				ft_quat_normalise(t_quat *out);
double				ft_quat_to_axis_angle(t_quat *q, t_vec3 *out);
void				ft_quat_from_euler_zyx(t_vec3 *v, t_quat *out);
void				ft_quat_to_euler_zyx(t_quat *q, t_vec3 *out);
void				ft_quat_conjugate(t_quat *q, t_quat *out);
void				ft_quat_mult(t_quat *q1, t_quat *q2, t_quat *out);
void				ft_quat_rotate(t_vec3 *v, t_quat *q, t_vec3 *out);
void				ft_quat_slerp(t_quat *q1, t_quat *q2, double t, \
		t_quat *out);

//VEC3_UTILS
t_vec3				ft_vec3_add(t_vec3 a, t_vec3 b);
t_vec3				ft_vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				ft_vec3_mult(t_vec3 v, double t);
t_vec3				ft_vec3_div(t_vec3 v, double t);
double				ft_vec3_dot(t_vec3 a, t_vec3 b);
t_vec3				ft_vec3_cross(t_vec3 a, t_vec3 b);
double				ft_vec3_length(t_vec3 v);
double				ft_vec3_length_squared(t_vec3 v);
t_vec3				ft_vec3_normalize(t_vec3 v);
t_vec3				ft_vec3_reflect(t_vec3 v, t_vec3 n);

#endif
