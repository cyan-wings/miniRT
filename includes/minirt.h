/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "ft_math_utils.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdlib.h>
# include "material.h"
# include "primitive.h"
# include "ray.h"
# include "scene.h"

# if defined(__APPLE__)
#  include "keys_macos.h"
# else
#  include "keys.h"
# endif

/* Window settings */
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define WIN_TITLE "miniRT"

/* Ray tracing constants */
# define MAX_DEPTH 10
# define EPSILON 1e-6
# define INFINITY_F 1e30
# define MAX_OBJECTS 100
# define DEFAULT_SCATTER_ANGLE 0.0
# define MAX_SCATTER_ANGLE 45.0
# define DEFAULT_RAYS_PER_PIXEL 1
# define MAX_RAYS_PER_PIXEL 1024

/* Error messages */
# define ERR_USAGE "Usage: ./miniRT [scene.rt]"
# define ERR_FILE "Error: Cannot open file"
# define ERR_PARSE "Error: Invalid scene format"
# define ERR_MALLOC "Error: Memory allocation failed"
# define ERR_MLX "Error: MLX initialization failed"

/* MLX data structure */
typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_data;

/* Main program structure */
typedef struct s_minirt
{
	t_scene		scene;
	t_mlx_data	mlx_data;
}	t_minirt;

/* Function prototypes */

/* Main */
int			main(int argc, char **argv);

/* Vector utilities - from libft ft_math_utils.h */
t_vec3		ft_vec3_refract(t_vec3 uv, t_vec3 n, double etai_over_etat);
t_vec3		ft_vec3_random_unit_vector(void);

/* Color utilities */
t_color		color_add(t_color a, t_color b);
t_color		color_multiply(t_color a, t_color b);
t_color		color_scale(t_color c, double t);
t_color		color_clamp(t_color a, double low, double high);
int			color_to_int(t_color c);
t_color		int_to_color(int color);

/* Ray utilities */
t_ray		ray_create(t_vec3 origin, t_vec3 direction);
t_vec3		ray_at(t_ray ray, double t);
t_ray		calc_refracted_ray(t_hit *hit, t_vec3 direction);
double		schlick_reflectance(double cosine, double ref_idx);

/* Camera */
void		camera_init(t_camera *camera);
t_vec3		camera_base_direction(t_camera *camera, double u, double v);
t_ray		camera_get_ray_scattered(t_camera *camera, t_vec3 direction,
				double jitter_u, double jitter_v);

/* Lighting */
t_color		calculate_lighting(t_hit hit, t_scene *scene, t_ray ray);

/* Renderer */
void		render_scene(t_minirt *minirt);
void		put_pixel(t_mlx_data *data, int x, int y, int color);

/* Material */
t_material	material_create(double ambient,
				double diffuse, double specular, double shininess);
t_material	material_create_glass(t_color tint, double refr_idx, double fuzz);

/* MLX utilities */
int			init_mlx(t_mlx_data *data);
int			handle_key(int keycode, t_minirt *minirt);
int			handle_close(t_minirt *minirt);
void		cleanup_mlx(t_mlx_data *data);

/* Error handling */
void		error_exit(const char *message);
void		cleanup_and_exit(t_minirt *minirt, const char *message);

/* Utilities */
char		**ft_split_whitespace(char const *s);
double		random_double(void);
double		random_double_range(double min, double max);

#endif
