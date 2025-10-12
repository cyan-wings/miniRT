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

# if defined(__APPLE__)
#  include "keys_macos.h"
# else
#  include "keys.h"
# endif

/* Window settings */
# define WIN_WIDTH 1920
# define WIN_HEIGHT 900
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

/* Color structure */
typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

/* Ray structure */
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

/* Material structure */
typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

/* Hit information */
typedef struct s_hit
{
	int			hit;
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_material	material;
}	t_hit;

/* Object types */
typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_object_type;

/* Sphere structure */
typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	material;
}	t_sphere;

/* Sphere intersection variables */
typedef struct s_sphere_intersect
{
	t_vec3 oc;
	double a;
	double b;
	double c;
	double discriminant;
}	t_sphere_intersect;

/* Plane structure */
typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_material	material;
}	t_plane;

/* Cylinder structure */
typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		axis;
	double		radius;
	double		height;
	t_material	material;
}	t_cylinder;

/* Object structure */
typedef struct s_object
{
	t_object_type		type;
	void				*data;
}	t_object;

/* Camera structure */
typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	up;
	t_vec3	right;
	double	fov;
	double	aspect_ratio;
	double	viewport_width;
	double	viewport_height;
	double	scatter_angle;
	int		rays_per_pixel;
}	t_camera;

/* Light structure */
typedef struct s_light
{
	t_vec3	position;
	t_color	color;
	double	brightness;
}	t_light;

/* Ambient light structure */
typedef struct s_ambient
{
	t_color	color;
	double	ratio;
}	t_ambient;

/* Scene structure */
typedef struct s_scene
{
	t_camera	camera;
	t_light		light;
	t_ambient	ambient;
	t_object	objects[MAX_OBJECTS];
	int			object_count;
}	t_scene;

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

/* Parser */
int			parse_scene(const char *filename, t_scene *scene);
int			parse_ambient(char **tokens, t_scene *scene);
int			parse_camera(char **tokens, t_scene *scene);
int			parse_light(char **tokens, t_scene *scene);
int			parse_sphere(char **tokens, t_scene *scene);
int			parse_plane(char **tokens, t_scene *scene);
int			parse_cylinder(char **tokens, t_scene *scene);

/* Vector utilities - from libft ft_math_utils.h */

/* Color utilities */
t_color		color_add(t_color a, t_color b);
t_color		color_mult(t_color c, double t);
t_color		color_multiply(t_color a, t_color b);
int			color_to_int(t_color c);
t_color		int_to_color(int color);

/* Ray utilities */
t_ray		ray_create(t_vec3 origin, t_vec3 direction);
t_vec3		ray_at(t_ray ray, double t);

/* Camera */
void		camera_init(t_camera *camera);
t_ray		camera_get_ray(t_camera *camera, double u, double v);
t_ray		camera_get_ray_scattered(t_camera *camera, double u, double v,
				double jitter_u, double jitter_v);

/* Collision detection */
t_hit		intersect_scene(t_ray ray, t_scene *scene);
t_hit		intersect_sphere(t_ray ray, t_sphere *sphere);
t_hit		intersect_plane(t_ray ray, t_plane *plane);
t_hit		intersect_cylinder(t_ray ray, t_cylinder *cylinder);

/* Lighting */
t_color		calculate_lighting(t_hit hit, t_scene *scene, t_ray ray);

/* Renderer */
void		render_scene(t_minirt *minirt);
t_color		trace_ray(t_ray ray, t_scene *scene, int depth);
void		put_pixel(t_mlx_data *data, int x, int y, int color);

/* Object management */
void		object_add(t_scene *scene, t_object_type type, void *data);
void		objects_free(t_scene *scene);

/* Material */
t_material	material_create(t_color color, double ambient,
				double diffuse, double specular, double shininess);

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
